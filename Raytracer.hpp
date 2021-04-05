#pragma once
#include "Sphere.hpp"
#include "Light.hpp"

class Raytracer {
public:
    int object_count_, light_count_;
    Sphere* objects_;
    Light* lights_;

    Raytracer(int object_count, Sphere* objects, int light_count, Light* lights);

    Vector trace(Ray ray, Sphere* object = nullptr);
    bool inshadow(Vector p, Vector lightpos);
    Vector color(Ray ray);

    Vector diffuse   (Sphere obj, Vector hit, Vector norm);
    Vector reflection(Sphere obj, Vector hit, Vector norm);
    Vector refraction(Sphere obj, Vector hit, Vector norm);
};