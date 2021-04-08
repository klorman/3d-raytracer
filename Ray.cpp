#include "Ray.hpp"

Ray::Ray(const Vector& start, const Vector& dir, double power) :
    start_(start),
    dir_  (dir),
    power_(power)
{}

Ray Ray::reflect(const Vector& norm, const Vector& hit, double refl) const {
    Vector dir = dir_ + norm * ((dir_ ^ norm) * (-2));
    return { hit + dir, dir, refl * power_ };
}