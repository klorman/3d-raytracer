#pragma once
#include "TXLib.h"
#include "Object.hpp"
#include <cassert>

class Cube : public Object {
public:
    Vector* vertexes_;
    double size_;

    Cube(Vector* vertexes, const Vector& color, const double& size);
    ~Cube() {};

    virtual Vector norm (const Vector& p  ) override;
    virtual Vector color(const Vector& p  ) override;
    virtual Vector trace(const Ray&    ray) override;

    Cube (const Cube&) = delete;
    Cube& operator=(const Cube&) = delete;
};
