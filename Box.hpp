#pragma once
#include "Object.hpp"

class Box : public Object {
public:
    Box(const Vector& center, const Vector& color, const double size, const Material& mat);

    virtual Vector color(const Vector& hit              ) const override;
    virtual Vector trace(const Ray&    ray, Vector* norm) const override;
};