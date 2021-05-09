#include "Object.hpp"

Sphere::Sphere(const Material& mat, const Vector& size, const Vector& center, const Vector& color, const Vector& rotation) :
    Object(mat, size, center, color, rotation)
{
    type = 1;
}

Vector Sphere::color(const Vector& hit) const {
    (void) hit;
    return color_;
}

Vector Sphere::trace(const Ray& ray, Vector* norm) const {
    Vector  ocn = (ray.start_ - center_) / size_, 
            rdn = ray.dir_ / size_;

    double  a = rdn ^ rdn, 
            b = ocn ^ rdn, 
            c = ocn ^ ocn, 
            h = b * b - a * (c - 1);

    if (h < 0 || b > 0) return NULLVEC;
    
    Vector hit = ray.start_;
    double dist = (-b - sqrt(h)) / a;
    
    if (dist > 0) hit += ray.dir_ * dist;
    else          hit += ray.dir_ * ((-b + sqrt(h)) / a);

    *norm =  ((hit - center_) / size_ / size_ * 2).norm();

//    if (status_) {
//        if (2 * sqrt(h) / a < 20) return hit;
//
//        return NULLVEC;
//    } 

    return hit;
}
