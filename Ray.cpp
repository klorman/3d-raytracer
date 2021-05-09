#include "Ray.hpp"
#include <cmath>
#include <cassert>
#include <random>

Ray::Ray() :
    start_     (NULLVEC),
    dir_       (NULLVEC),
    generation_(0),
    n1         (0)
{}

Ray::Ray(const Vector& start, const Vector& dir, int generation, double n) :
    start_     (start),
    dir_       (dir),
    generation_(generation),
    n1         (n)
{}

Ray Ray::reflect(const Vector& norm, const Vector& hit, double roughness) const {
    Vector dir = dir_ - norm * ((dir_ ^ norm) * 2);

    Vector diffuse = random_on_sphere();
    diffuse = (diffuse * (diffuse ^ norm)).norm();

    dir = mix(diffuse, dir, roughness);

    return { hit + dir * EPS, dir, generation_ + 1 };
}

Ray Ray::refract(const Vector& norm, const Vector& hit, double n2) const {
    assert(n1 > 0 && n2 > 0);

    double nd = norm ^ dir_;

    if (nd > 0) {
        return refract(-norm, hit, 1 / n2);
    }

    double eta = n1 / n2,
           k = 1 - eta * eta * (1 - pow(nd, 2));

    Vector dir = EVEC;

    if (k >= 0) dir = dir_ * eta - norm * (eta * nd + sqrt(k));

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

Vector random_on_box(double sizeX, double sizeY) {
    assert(sizeX > 0 && sizeY > 0);

    return { unif(re) * sizeX, unif(re) * sizeY, 0 };
}