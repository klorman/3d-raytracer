#pragma once
#include "TXLib.h"
#include "Ray.hpp"

#include <cmath>
#include <cassert>

struct Material {
    double reflection, n, transparency, roughness;
};

class Object {
public:
    Material mat_;
    double size_;
    Vector center_, color_, rotation_;

    Object();
    Object(const Material& mat, double size, const Vector& center, const Vector& color, const Vector& rotation = {0,0,1});
    virtual ~Object() = default;

    virtual Vector color(const Vector& hit              ) const = 0;
    virtual Vector trace(const Ray&    ray, Vector* norm) const = 0;
};

class Box : public Object {
public:
    Box(const Vector& center, const Vector& color, const double size, const Material& mat);

    virtual Vector color(const Vector& hit              ) const override;
    virtual Vector trace(const Ray&    ray, Vector* norm) const override;
};

class Sphere : public Object {
public:
    Sphere(const Vector& center, const Vector& color, const double size, const Material& mat);

    virtual Vector color(const Vector& hit              ) const override;
    virtual Vector trace(const Ray&    ray, Vector* norm) const override;
};

class Plane : public Object {
public:
    Vector dir_;

    Plane(const Vector& center, const Vector& color, const Vector& dir, const Material& mat);

    virtual Vector color(const Vector& hit              ) const override;
    virtual Vector trace(const Ray&    ray, Vector* norm) const override;
};