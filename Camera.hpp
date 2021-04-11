#pragma once

#include "Vector.hpp"

class Camera {
public:
    double speed_;
    Vector pos_, dir_;

    bool move();
};