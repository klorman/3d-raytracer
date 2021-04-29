#pragma once
#include "TXLib.h"
#include "Ray.hpp"
#include "Matrix.hpp"

#include <cmath>
#include <cassert>

struct Material {
    double reflection, n, transparency, roughness;
};

class Object {
public:
    Material mat_;
    Vector size_, center_, color_, rotation_;
    mat4 txx, txi;
    int type;
    HDC image_;

    Object();
    Object(const Material& mat, const Vector& size, const Vector& center, const Vector& color, const Vector& rotatio = {0,-1,0});
    virtual ~Object() = default;

    void createImage();

    virtual Vector color(const Vector& hit              ) const = 0;
    virtual Vector trace(const Ray&    ray, Vector* norm) const = 0;
};

class Box : public Object {
public:
    Box   (const Material& mat, const Vector& size, const Vector& center, const Vector& color, const Vector& rotation = NULLVEC);

    virtual Vector color(const Vector& hit              ) const override;
    virtual Vector trace(const Ray&    ray, Vector* norm) const override;
};

class Sphere : public Object {
public:
    Sphere(const Material& mat, const Vector& size, const Vector& center, const Vector& color, const Vector& rotation = NULLVEC);

    virtual Vector color(const Vector& hit              ) const override;
    virtual Vector trace(const Ray&    ray, Vector* norm) const override;
};

class Plane : public Object {
public:
    Plane (const Material& mat, const Vector& center, const Vector& color, const Vector& rotation);

    virtual Vector color(const Vector& hit              ) const override;
    virtual Vector trace(const Ray&    ray, Vector* norm) const override;
};