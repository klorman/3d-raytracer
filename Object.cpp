#include "Object.hpp"

Object::Object() :
    center_({0, 0, 0}),
    color_ ({0, 0, 0}),
    mat_   ({0, 0, 0})
{}

Object::Object(const Vector& center, const Vector& color, const Material& mat) :
    center_(center),
    color_(color),
    mat_(mat)
{}