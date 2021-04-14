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
//    assert(n1 != 0 && n2 != 0);
//
//    if ((norm ^ dir_) > 0) {
//        return refract(-norm, hit, 1);
//    }
//
//    Vector S1 = hit - start_;
//    double n = n1 / n2, cos = (-S1) ^ norm, len = 1 + n * n * (cos * cos - 1);
//
//    if (len < 0) return {};
//
//    Vector dir = norm * n * cos + S1 * n - norm * sqrt(len);
//
//    return { hit + dir * EPS, dir, generation_ + 1, n2 };

    assert(n1 != 0 && n2 != 0);
    double nd = norm ^ dir_, a = 1 / n2;
    if (nd > 0) {
        return refract(-norm, hit, a);
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