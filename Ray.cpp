#include "Ray.hpp"
#include <cmath>
#include <cassert>
#include <random>

Ray::Ray() :
    start_     (NULLVEC),
    dir_       (NULLVEC),
    generation_(0)
{}

Ray::Ray(const Vector& start, const Vector& dir, int generation) :
    start_     (start),
    dir_       (dir),
    generation_(generation)
{}

Ray& Ray::reflect(const Vector& norm, const Vector& hit, double roughness) {
    Vector dir = dir_ - norm * ((dir_ ^ norm) * 2);

    Vector diffuse = random_on_sphere();
    diffuse = (diffuse * (diffuse ^ norm)).norm();

    dir = mix(diffuse, dir, roughness);

    start_ = hit + dir * EPS;
    dir_   = dir;
    ++generation_;

    return (*this);
}

Ray Ray::refract(const Vector& norm, const Vector& hit, double refr, double transparency) const {
    assert(refr != 0);
    double nd = norm ^ dir_, a = 1 / refr;

    if (nd > 0) {
        return refract(-norm, hit, a, transparency);
    }

    double D = 1 - a * a * (1 - nd * nd);
    
    if (D < 0) {
        return {};
    }

    double b = nd * a + sqrt(D);
    Vector dir = dir_ * a - norm * b;

    return { hit + dir * EPS, dir, generation_ + 1 };
}

std::default_random_engine re;
std::uniform_real_distribution<double> unif(-1, 1);

Vector random_on_sphere() {
    Vector rnd;

    while(true) {
        rnd = Vector { unif(re), unif(re), unif(re) };
    
        if (rnd.length() <= 1) break;
    }

    return rnd;
}