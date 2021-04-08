#pragma once
#include "TXLib.h"
#include "Ray.hpp"

struct Material {
    double reflection, transparency, surface;
};

class Object {
public:
    Vector center_, color_;
    Material mat_;

    Object();
    Object(const Vector& center, const Vector& color, const Material& mat);

    virtual Vector norm (const Vector& p  ) = 0;
    virtual Vector color() = 0;
    virtual Vector trace(const Ray&    ray) = 0;
};