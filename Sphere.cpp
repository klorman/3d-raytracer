#include "Object.hpp"

Sphere::Sphere(const Material& mat, const Vector& size, const Vector& center, const Vector& color) :
    Object(mat, size, center, color)
{}

Vector Sphere::color(const Vector& hit) const {
    (void) hit;
    return color_;
}

Vector Sphere::trace(const Ray& ray, Vector* norm) const {
    if ((center_ - ray.start_).length() < size_.x_) {
        double r2 = size_.x_ * size_.x_;
        double dist2 =  pow((center_ - ray.start_).length(), 2);
        double projection = (center_ - ray.start_) ^ ray.dir_;
     
        double h2 = dist2 - projection * projection;
     
        if (h2 > r2) {
            return NULLVEC;
        }
     
        Vector hit = ray.start_ + ray.dir_ * (projection + sqrt(r2 - h2));

        *norm = (hit - center_) / size_;

        return hit;
    }

    Vector  ocn = (ray.start_ - center_) / size_, 
            rdn = ray.dir_ / size_;

    double  a = rdn ^ rdn, 
            b = ocn ^ rdn, 
            c = ocn ^ ocn, 
            h = b * b - a * (c - 1);

    if (h < 0 || b > 0) return NULLVEC;
    
    Vector hit = ray.start_ + ray.dir_ * ((-b - sqrt(h)) / a);

    *norm =  ((hit - center_) / size_ / size_ * 2).norm();

    return hit;
}
