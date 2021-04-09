#include "Light.hpp"

Light::Light(const Vector& center, const Vector& color, double power) :
    Sphere(center, color, power * 10, { 0, 0, 0, 1 }),
    power_(power)
{}
