#include "Plane.hpp"

Plane::Plane(const Vector& center, const Vector& color, const Vector& dir, const Material& mat) :
    Object(center, color, mat),
    dir_(dir)
{}

Vector Plane::norm(const Vector& p, const Vector& from) {
    return dir_ * SIGN((from - p) ^ dir_);
}

Vector Plane::color(const Vector& hit) {
    if (((int) hit.x_ % 50 > 25 || (int) hit.x_ % 50 > -25) ^
        ((int) hit.z_ % 50 > 25 || (int) hit.z_ % 50 > -25))
        return EVEC / 10;

    return color_;
}

Vector Plane::trace(const Ray& ray) {
    Vector norm = (*this).norm(center_, ray.start_);

    double D = -center_ ^ norm, den = ray.dir_ ^ norm;
    
    if (den < 0) {
        double dist = -(D + (ray.start_ ^ norm)) / den;
        return ray.start_ + ray.dir_ * dist;
    }

    return NULLVEC;
}