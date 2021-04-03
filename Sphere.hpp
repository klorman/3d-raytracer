#pragma once
#include "TXLib.h"
#include "Ray.hpp"
#include <cassert>

class Sphere {
public:
    Vector center_, color_;
    double radius_;

    Sphere(const Vector& center, const double& radius);

    Vector norm (const Vector& p  );
    Vector color(const Vector& p  );
    Vector trace(const Ray&    ray);
};