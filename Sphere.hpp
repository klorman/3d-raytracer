#pragma once
#include "Object.hpp"
#include <cassert>

class Sphere : public Object {
public:
    double radius_;

    Sphere(const Vector& center, const Vector& color, const double& radius, const Material& mat);

    virtual Vector norm (const Vector& p, const Vector& from) const override;
    virtual Vector color(const Vector& hit)                   const override;
    virtual Vector trace(const Ray& ray)                      const override;
};