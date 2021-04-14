#include "Plane.hpp"

Plane::Plane(const Vector& center, const Vector& color, const Vector& dir, const Material& mat) :
    Object(mat, 0, center, color),
    dir_(dir)
{}

Vector Plane::color(const Vector& hit) const {
    if (((int) hit.x_ % 50 > 25 || (int) hit.x_ % 50 > -25) ^
        ((int) hit.z_ % 50 > 25 || (int) hit.z_ % 50 > -25))
        return EVEC / 8;

    return color_;
}

Vector Plane::trace(const Ray& ray, Vector* norm) const {
    *norm = dir_ * sign((ray.start_ - center_) ^ dir_);

    double D = -center_ ^ *norm, den = ray.dir_ ^ *norm;
    
    if (den < 0) {
        double dist = -(D + (ray.start_ ^ *norm)) / den;
        return ray.start_ + ray.dir_ * dist;
    }

    return NULLVEC;
}