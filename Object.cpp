#include "Object.hpp"

Object::Object(const Vector& center, const Vector& color, const Material& mat) :
    center_(center),
    color_(color),
    mat_(mat)
{}