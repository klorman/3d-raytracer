#pragma once
#include "TXLib.h"
#include "Object.hpp"
#include <cassert>

class Sphere : public Object {
public:
    Vector center_;
    double radius_;

    Sphere();
    Sphere(const Vector& center, const Vector& color, const double& radius);
    ~Sphere() {};

    virtual Vector norm (const Vector& p  ) override;
    virtual Vector color(const Vector& p  ) override;
    virtual Vector trace(const Ray&    ray) override;
};