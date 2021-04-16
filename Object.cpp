#include "Object.hpp"

Object::Object(const Material& mat, const Vector& size, const Vector& center, const Vector& color, const Vector& rotation) :
    mat_     (mat),
    size_    (size),
    center_  (center),
    color_   (color),
    rotation_(rotation)
{}