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
    //mat4 txx, txi;
    int type;
    bool status_;

    Object();
    Object(const Material& mat, const Vector& size, const Vector& center, const Vector& color, const Vector& rotatio = {0,-1,0});
    virtual ~Object() = default;

    virtual Vector     color(const Vector& hit              ) const = 0;
    virtual VectorPair trace(const Ray&    ray, Vector* norm) const = 0;
};

class Box : public Object {
public:
    Box   (const Material& mat, const Vector& size, const Vector& center, const Vector& color, const Vector& rotation = NULLVEC);

    virtual Vector     color(const Vector& hit              ) const override;
    virtual VectorPair trace(const Ray&    ray, Vector* norm) const override;
};

class Sphere : public Object {
public:
    Sphere(const Material& mat, const Vector& size, const Vector& center, const Vector& color, const Vector& rotation = NULLVEC);

    virtual Vector     color(const Vector& hit              ) const override;
    virtual VectorPair trace(const Ray&    ray, Vector* norm) const override;
};

class Plane : public Object {
public:
    Plane (const Material& mat, const Vector& center, const Vector& color, const Vector& rotation);

    virtual Vector     color(const Vector& hit              ) const override;
    virtual VectorPair trace(const Ray&    ray, Vector* norm) const override;
};

class Lens : public Object {
public:
    Sphere sphere1_, sphere2_;

    Lens (const Material& mat, const Vector& size1, const Vector& size2, const Vector& center1, const Vector& center2, const Vector& color, const Vector& rotation = NULLVEC);

    virtual Vector     color(const Vector& hit              ) const override;
    virtual VectorPair trace(const Ray&    ray, Vector* norm) const override;
};

std::vector<double> sortFour(double a, double b, double c, double d);