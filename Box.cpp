#include "Object.hpp"

Box::Box(const Material& mat, const Vector& size, const Vector& center, const Vector& color, const Vector& rotation) :
    Object(mat, size, center, color, rotation)
{}

Vector Box::color(const Vector& hit) const {
    (void) hit;
    return color_;
}

Vector Box::trace(const Ray& ray, Vector* norm) const {
    Vector m = EVEC / ray.dir_,
           n = m * (ray.start_ - center_),
           k = abs(m) * size_,
           t1 = -n - k,
           t2 = -n + k;

    double tN = std::max(std::max(t1.x_, t1.y_), t1.z_),
           tF = std::min(std::min(t2.x_, t2.y_), t2.z_);

    if (tN > tF || tF < 0) return NULLVEC;

    *norm = -sign(ray.dir_) * step({ t1.y_, t1.z_, t1.x_ }, { t1.x_, t1.y_, t1.z_ }) * step({ t1.z_, t1.x_, t1.y_ }, { t1.x_, t1.y_, t1.z_ });

    return ray.start_ + ray.dir_ * tN;
}