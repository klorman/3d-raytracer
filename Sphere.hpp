#pragma once
#include "Object.hpp"
#include <cassert>

class Sphere : public Object {
public:
    Sphere(const Vector& center, const Vector& color, const double size, const Material& mat);

    //virtual Vector norm (const Vector& p, const Vector& from) const override;
    virtual Vector color(const Vector& hit              ) const override;
    virtual Vector trace(const Ray&    ray, Vector* norm) const override;
};