#pragma once
#include "Sphere.hpp"

class Light : public Sphere {
public:
    double power_;

    Light(const Vector& center, const Vector& color, double power);
};