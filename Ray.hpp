#pragma once
#include "Vector.hpp"

class Ray {
public:
    Vector start_, dir_, color_;
    int generation_;

    Ray();
    Ray(const Vector& start, const Vector& dir, const Vector& color = 1, int generation = 0);

    Ray reflect(const Vector& norm, const Vector& hit, const Vector& color) const;
    Ray refract(const Vector& norm, const Vector& hit, double refr, double transparency) const;
};