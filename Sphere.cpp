#include "Sphere.hpp"

Sphere::Sphere(const Vector& center, const Vector& color, const double size, const Material& mat) :
    Object(mat, size, center, color)
{}

Vector Sphere::color(const Vector& hit) const {
    (void) hit;
    return color_;
}

Vector Sphere::trace(const Ray& ray, Vector* norm) const {
    double r2 = size_ * size_;
    double dist2 =  pow((center_ - ray.start_).length(), 2);
    double projection = (center_ - ray.start_) ^ ray.dir_;

    if (dist2 > r2 && projection < 0) {
        return NULLVEC;
    }

    double h2 = dist2 - projection * projection;

    if (h2 > r2) {
        return NULLVEC;
    }

    Vector hit = ray.start_;

    ((center_ - ray.start_).length() <= size_) ? hit += ray.dir_ * (projection + sqrt(r2 - h2)) : 
                                                 hit += ray.dir_ * (projection - sqrt(r2 - h2));

    *norm = (hit - center_) / size_; //что то не так, не понимаю, в чем дело

    return hit;
}
