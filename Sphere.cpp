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

VectorPair Sphere::trace(const Ray& ray, Vector* norm) const {
    Vector  ocn = (ray.start_ - center_) / size_, 
            rdn = ray.dir_ / size_;

    double  a = rdn ^ rdn, 
            b = ocn ^ rdn, 
            c = ocn ^ ocn, 
            h = b * b - a * (c - 1);

    if (h < 0 || b > 0) return {NULLVEC, NULLVEC};
    
    //Vector hit = ray.start_;
    //double dist = (-b - sqrt(h)) / a;
    double tN = (-b - sqrt(h)) / a,
           tF = (-b + sqrt(h)) / a;
    
    //if (dist > 0) hit += ray.dir_ * dist;
    //else          hit += ray.dir_ * ((-b + sqrt(h)) / a);

    *norm =  ((ray.start_ + ray.dir_ * (tN > 0 ? tN : tF) - center_) / size_ / size_ * 2).norm();

    return {ray.start_ + ray.dir_ * tN, ray.start_ + ray.dir_ * tF};
}
