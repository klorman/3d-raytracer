#pragma once
#include "TXLib.h"
#include "Ray.hpp"

#include <cmath>

#define SIGN(x) (((x) < 0) ? -1 : ((x) > 0 ))

struct Material {
    double reflection, n, transparency, roughness;
};

class Object {
public:
    Material mat_;
    double size_;
    Vector center_, color_, rotation_;

    Object();
    Object(const Material& mat, double size, const Vector& center, const Vector& color, const Vector& rotation = {0,0,1});
    virtual ~Object() = default;

    //virtual Vector norm (const Vector& p, const Vector& from) const = 0;
    virtual Vector color(const Vector& hit              ) const = 0;
    virtual Vector trace(const Ray&    ray, Vector* norm) const = 0;
};