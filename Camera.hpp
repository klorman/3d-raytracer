#pragma once

#include "Vector.hpp"

class Camera {
public:
    Vector pos_, dir_;

    void move();
};