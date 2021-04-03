#include "Raytracer.hpp"

Raytracer::Raytracer(Sphere* objects, size_t count) :
    objects_(objects),
    count_(count)
{}

Vector Raytracer::trace(Ray ray) {
    Vector p;

    for (int obj = 0; obj < count_; obj++) {
        
    }
}