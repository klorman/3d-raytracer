#include "Sphere.hpp"
#include <cmath>

Sphere::Sphere(const Vector& center, const double& radius) :
    center_(center),
    radius_(radius)
{}

Vector Sphere::norm (const Vector& p  ) {
    return (p - center_) / radius_;
}

Vector Sphere::color(const Vector& p  ) {
    return color_;
}

Vector Sphere::trace(const Ray&    ray) {
    Vector OS = ray.start_ - center_;
    double dot = ray.dir_ ^ OS;

    assert(dot <= 0);

    double qd = (OS ^ OS) - radius_ * radius_, D = dot * dot - qd;
    double t = qd > 0 ? -dot - sqrt(D) : -dot + sqrt(D);

    return ray.start_ + ray.dir_ * t;
}
