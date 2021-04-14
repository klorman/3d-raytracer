#pragma once
#include "Object.hpp"
#include "Sphere.hpp"
#include "Plane.hpp"
#include "Camera.hpp"

const Vector background_color = { 0.5, 0.5, 1.0 };

class Raytracer {
public:
    int object_count_;
    Object** objects_;

    Raytracer(int object_count, Object** objects);

    Vector trace(const Ray& ray, int* object = nullptr, Vector* norm = nullptr);
    Vector color(const Ray& ray);

    Vector reflection(Object* obj, const Vector& hit, const Vector& norm, const Ray& ray);
    Vector refraction(Object* obj, const Vector& hit, const Vector& norm, const Ray& ray);
};