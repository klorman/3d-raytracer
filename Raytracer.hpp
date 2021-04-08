#pragma once
#include "Object.hpp"
#include "Light.hpp"

const Vector background_color = { 0, 128, 0 };

class Raytracer {
public:
    int object_count_, light_count_;
    Object** objects_;
    Light* lights_;

    Raytracer(int object_count, Object** objects, int light_count, Light* lights);

    Vector trace (const Ray& ray, int* object = nullptr);
    bool inshadow(const Vector& p, const Vector& lightpos);
    Vector color (const Ray& ray);

    Vector diffuse   (Object* obj, const Vector& hit, const Vector& norm);
    Vector reflection(Object* obj, const Vector& hit, const Vector& norm, const Ray& ray);
    Vector refraction(Object* obj, const Vector& hit, const Vector& norm);
};