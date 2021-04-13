#pragma once

#include "Object.hpp"

class Plane : public Object {
public:
    Vector dir_;

    Plane(const Vector& center, const Vector& color, const Vector& dir, const Material& mat);

    virtual Vector norm (const Vector& p, const Vector& from) override;
    virtual Vector color(const Vector& hit                  ) override;
    virtual Vector trace(const Ray&    ray                  ) override;
};