#include "Plane.hpp"
#include <iostream>

Plane::Plane(const Vector& center, const Vector& color, const Vector& dir, const Material& mat) :
    Object(center, color, mat),
    dir_(dir)
{}

Vector Plane::norm (const Vector& p  ) {
    (void)p;
    return dir_; //нужно переделать так, чтобы работало с обратной стороны плоскости
}

Vector Plane::color(const Vector& hit) {
    if (((int) hit.x_ % 50 > 25 || (int) hit.x_ % 50 > -25) ^
        ((int) hit.z_ % 50 > 25 || (int) hit.z_ % 50 > -25))
        return { 0, 0, 0 };

    return color_;
}

Vector Plane::trace(const Ray&    ray) {
    double D = -center_ ^ dir_, den = ray.dir_ ^ dir_;
    
    if (den < 0) {
        double dist = -(D + (ray.start_ ^ dir_)) / den;
        return ray.start_ + ray.dir_ * dist;
    }

    return NULLVEC;
}