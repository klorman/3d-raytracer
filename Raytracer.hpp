#pragma once
#include "Sphere.hpp"

class Raytracer {
public:
    size_t count_;
    Sphere* objects_;

    Raytracer(Sphere* objects, size_t count);

    Vector trace(Ray ray);
};