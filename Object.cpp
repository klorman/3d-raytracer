#include "Object.hpp"

Object::Object(const Material& mat, const Vector& center, const Vector& color, const Vector& rotation) :
    mat_     (mat),
    center_  (center),
    color_   (color),
    rotation_(rotation)
{}