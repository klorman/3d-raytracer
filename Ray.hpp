#pragma once
#include "Vector.hpp"

#define MAXGEN 10

class Ray {
public:
    Vector start_, dir_, color_;
    int generation_;

    Ray();
    Ray(const Vector& start, const Vector& dir, int generation = 0);

    Ray& reflect(const Vector& norm, const Vector& hit, double roughness);
    Ray  refract(const Vector& norm, const Vector& hit, double refr, double transparency) const;
};

Vector random_on_sphere();