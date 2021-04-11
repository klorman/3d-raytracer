#include "Ray.hpp"
#include <cmath>
#include <cassert>

Ray::Ray() :
    start_     (NULL),
    dir_       (NULL),
    color_     (NULL),
    generation_(NULL)
{}

Ray::Ray(const Vector& start, const Vector& dir, const Vector& color, int generation) :
    start_     (start),
    dir_       (dir),
    color_     (color),
    generation_(generation)
{}

Ray Ray::reflect(const Vector& norm, const Vector& hit, const Vector& color) const {
    Vector dir = dir_ + norm * ((dir_ ^ norm) * (-2));
    return { hit + dir * 0.01, dir, color_ * color, generation_ + 1 };
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

    return { hit + dir * 0.01, dir, color_ * transparency, generation_ + 1 };
}