#include "Sphere.hpp"
#include <cmath>

Sphere::Sphere(const Vector& center, const Vector& color, const double& radius, const Material& mat) :
    Object(center, color, mat),
    radius_(radius)
{}

Vector Sphere::norm (const Vector& p  ) {
    return (p - center_) / radius_;
}

Vector Sphere::color() {
    return color_;
}

Vector Sphere::trace(const Ray&    ray) {
    double r2 = radius_ * radius_;
    double dist2 =  pow((center_ - ray.start_).length(), 2);
    double projection = (center_ - ray.start_) ^ ray.dir_;

    if (dist2 > r2 && projection < 0) {
        return NULL;
    }

    double h2 = dist2 - projection * projection;

    if (h2 > r2) {
        return NULL;
    }

    return ray.start_ + ray.dir_ * (projection - sqrt(r2 - h2));
}
