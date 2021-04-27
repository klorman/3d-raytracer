#pragma once

#include "Object.hpp"
#include "Properties.hpp"

#include <vector>

//const Vector background_color = { 0.5, 0.5, 1.0 };

class Raytracer {
public:
    int object_count_;
    std::vector<Object*> objects_;
    Properties* prop_;

    Raytracer();
    Raytracer(int object_count, std::vector<Object*> objects, Properties* prop);

    Vector trace(const Ray& ray, int* object = nullptr, Vector* norm = nullptr);
    Vector color(const Ray& ray);

    Vector reflection(Object* obj, const Vector& hit, const Vector& norm, const Ray& ray);
    Vector refraction(Object* obj, const Vector& hit, const Vector& norm, const Ray& ray);

    void addObject(Object* object);

    Raytracer(const Raytracer&) = delete;
    Raytracer& operator=(const Raytracer&) = delete;
};