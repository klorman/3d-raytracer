#include "Plane.hpp"
#include <iostream>

Plane::Plane(const Vector& center, const Vector& color, const Vector& dir, const Material& mat) :
    Object(center, color, mat),
    dir_(dir)
{}

Vector Plane::norm (const Vector& p  ) {
    return dir_;
}

Vector Plane::color() {
    return color_;
}

Vector Plane::trace(const Ray&    ray) {
    double D = -center_ ^ dir_, den = ray.dir_ ^ dir_;
    
    if (den < 0) {
        double dist = -(D + (ray.start_ ^ dir_)) / den;
        return ray.start_ + ray.dir_ * dist;
    }

    return NULL;
}