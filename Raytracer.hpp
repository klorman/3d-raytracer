#pragma once
#include "Object.hpp"
#include "Sphere.hpp"
#include "Plane.hpp"
#include "Light.hpp"
#include "Camera.hpp"

const Vector background_color = { 50, 50, 255 };

class Raytracer {
public:
    int object_count_, light_count_;
    Object** objects_;
    Light* lights_;

    Raytracer(int object_count, Object** objects, int light_count, Light* lights);

    Vector trace  (const Ray& ray, int* object = nullptr);
    double shading(const Vector& p, const Light& light);
    Vector color  (const Ray& ray);

    Vector diffuse   (Object* obj, const Vector& hit, const Vector& norm);
    Vector reflection(Object* obj, const Vector& hit, const Vector& norm, const Ray& ray);
    Vector refraction(Object* obj, const Vector& hit, const Vector& norm, const Ray& ray);
};