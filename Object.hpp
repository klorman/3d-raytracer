#pragma once
#include "TXLib.h"
#include "Ray.hpp"

struct Material {
    double reflection, refraction, transparency, roughness;
};

class Object {
public:
    Vector center_, color_;
    Material mat_;

    Object();
    Object(const Vector& center, const Vector& color, const Material& mat);
    virtual ~Object() = default;

    virtual Vector norm (const Vector& p  ) = 0;
    virtual Vector color(const Vector& hit) = 0;
    virtual Vector trace(const Ray&    ray) = 0;
};