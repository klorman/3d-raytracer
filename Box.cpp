#include "Box.hpp"

Box::Box(const Vector& center, const Vector& color, const double size, const Material& mat) :
    Object(mat, size, center, color)
{}

//Vector Box::norm(const Vector& p, const Vector& from) const {
//
//}

//Vector Box::color(const Vector& hit) const {
//    (void) hit;
//    return color_;
//}
//
//Vector Box::trace(const Ray& ray, Vector* norm) const {
//
//}
