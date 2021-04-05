#pragma once
#include "TXLib.h"
#include "Ray.hpp"
#include <cassert>

struct Material {
    Vector reflection, transparency, surface;
};
class Sphere {
public:
    Vector center_, color_;
    double radius_;
    Material mat_;

    Sphere();
    Sphere(const Vector& center, const Vector& color, const double& radius, Material mat);

    Vector norm (const Vector& p  );
    Vector color();
    Vector trace(const Ray&    ray);
};