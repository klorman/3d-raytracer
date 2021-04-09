#include "Light.hpp"

Light::Light(const Vector& center, const Vector& color, double radius, double power) :
    Sphere(center, color, radius, { 0, 0, 0, 1 }),
    power_(power)
{}
