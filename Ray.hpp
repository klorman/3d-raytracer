#pragma once

//#include "Vector.hpp"
#include "Properties.hpp"

class Ray {
public:
    Vector start_, dir_;
    int generation_;
    double n1;

    Ray();
    Ray(const Vector& start, const Vector& dir, int generation = 0, double n = 1);

    Ray reflect(const Vector& norm, const Vector& hit, double roughness) const;
    Ray refract(const Vector& norm, const Vector& hit, double n2) const;
};

Vector random_on_sphere();
Vector random_on_box(double sizeX, double sizeY);