#pragma once
#include "Vector.hpp"

class Ray {
public:
    Vector start_, dir_;
    double power_;
    int generation_;

    Ray();
    Ray(const Vector& start, const Vector& dir, double power = 1, int generation = 0);

    Ray reflect(const Vector& norm, const Vector& hit, double refl) const;
    Ray refract(const Vector& norm, const Vector& hit, double refr, double transparency) const;
};