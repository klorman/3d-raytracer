#include "Object.hpp"

Box::Box(const Material& mat, const Vector& size, const Vector& center, const Vector& color, const Vector& rotation) :
    Object(mat, size, center, color, rotation)
{
    type = 2;
}

Vector Box::color(const Vector& hit) const {
    (void) hit;
    return color_;
}

VectorPair Box::trace(const Ray& ray, Vector* norm) const {
    //double d1[] = {ray.dir_.x_,   ray.dir_.y_,   ray.dir_.z_,   0.0},
    //       d2[] = {ray.start_.x_, ray.start_.y_, ray.start_.z_, 1.0};

    //Vector rdd = (vec4) d1 * txx,
    //       roo = (vec4) d2 * txx;

    Vector m = EVEC / ray.dir_,
           n = m * (ray.start_ - center_),
           k = abs(m) * size_,
           t1 = -n - k,
           t2 = -n + k;

    double tN = std::max(std::max(t1.x_, t1.y_), t1.z_),
           tF = std::min(std::min(t2.x_, t2.y_), t2.z_);

    if (tN > tF || tF < 0) return {NULLVEC, NULLVEC};

    *norm = -sign(ray.dir_) * step({ t1.y_, t1.z_, t1.x_ }, { t1.x_, t1.y_, t1.z_ }) * step({ t1.z_, t1.x_, t1.y_ }, { t1.x_, t1.y_, t1.z_ });

    //if (tN < 0) return ray.start_ + ray.dir_ * tF;

    //return ray.start_ + ray.dir_ * tN;

    return {ray.start_ + ray.dir_ * tN, ray.start_ + ray.dir_ * tF};
}