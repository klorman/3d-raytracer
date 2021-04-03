#include "Sphere.hpp"
#include <Vector.hpp>
#include <cmath>

Sphere::Sphere(const Vector& center, const double& radius) :
    center_(center),
    radius_(radius)
{}

Vector Sphere::norm (const Vector& p  ) {
    return (p - center_) / radius_;
}

Vector Sphere::color(const Vector& p  ) {
    return color_;
}

Vector Sphere::trace(const Vector& ray) {

}
