#pragma once
#include "Ray.hpp"

struct Material {
    Vector reflection, transparency, surface;
};

class Object {
public:
    Vector color_;
    Material mat_;

    Object(const Vector& color);
    virtual ~Object() {};

    virtual Vector norm (const Vector& p  );
    virtual Vector color(const Vector& p  );
    virtual Vector trace(const Ray&    ray);
};