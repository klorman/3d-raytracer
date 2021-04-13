#include "Sphere.hpp"

Sphere::Sphere(const Vector& center, const Vector& color, const double& radius, const Material& mat) :
    Object(center, color, mat),
    radius_(radius)
{}

Vector Sphere::norm(const Vector& p, const Vector& from) {
    Vector norm = (p - center_) / radius_; 
    return norm * SIGN((from - p) ^ norm);
}

Vector Sphere::color(const Vector& hit) {
    (void) hit;
    return color_;
}

Vector Sphere::trace(const Ray& ray) {
    double r2 = radius_ * radius_;
    double dist2 =  pow((center_ - ray.start_).length(), 2);
    double projection = (center_ - ray.start_) ^ ray.dir_;

    if (dist2 > r2 && projection < 0) {
        return NULLVEC;
    }

    double h2 = dist2 - projection * projection;

    if (h2 > r2) {
        return NULLVEC;
    }

    if ((center_ - ray.start_).length() <= radius_) return ray.start_ + ray.dir_ * (projection + sqrt(r2 - h2)); //костыль для преломления
    return ray.start_ + ray.dir_ * (projection - sqrt(r2 - h2));
}
