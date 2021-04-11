#pragma once
#include "Sphere.hpp"

class Light : public Sphere { //этот класс уже не нужен
public:
    double power_;

    Light(const Vector& center, const Vector& color, double radius, double power);
};