#pragma once
#include "Vector.hpp"

class Ray {
public:
    Vector start_, dir_;

    Ray(Vector start, Vector dir);
};