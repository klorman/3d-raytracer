#include "Object.hpp"

Object::Object(const Material& mat, const Vector& size, const Vector& center, const Vector& color, const Vector& rotatio) :
    mat_     (mat),
    size_    (size),
    center_  (center),
    color_   (color),
    rotation_(rotatio),
    txx      (),
    txi      (),
    type     (-1)
{
    mat4 rot = rotation(Vector {0,1,0}.norm(), 30);
    mat4 tra = translate(center_);
    txi = tra * rot;
    txx = inverse(txi);
}