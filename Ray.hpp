#pragma once
#include "Vector.hpp"

class Ray {
public:
    Vector start_, dir_;
    double power_;

    Ray(Vector start, Vector dir, double power = 1);

    Ray reflect(const Vector& norm, const Vector& hit, double refl = 1) const;
};