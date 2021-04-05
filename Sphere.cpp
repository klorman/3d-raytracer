#include "Sphere.hpp"
#include <cmath>


Sphere::Sphere() :
    center_({ 0, 0, 0 }),
    color_({ 0, 0, 0 }),
    radius_(0),
    mat_({ 0, 0, 0 })
{}

Sphere::Sphere(const Vector& center, const Vector& color, const double& radius, Material mat) :
    center_(center),
    color_(color),
    radius_(radius),
    mat_(mat)
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
/*
    Vector OS = ray.start_ - center_;
    double dot = ray.dir_ ^ OS;
    
    //assert(dot <= 0);

    double qd = (OS ^ OS) - radius_ * radius_, D = dot * dot - qd;
    assert(D > 0);
    double t = qd > 0 ? -dot - sqrt(D) : -dot + sqrt(D);

    return ray.start_ + ray.dir_ * t;
*/
}
