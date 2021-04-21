#pragma once

#include "Matrix.hpp"

class Camera {
public:
    double speed_;
    Vector pos_, dir_, angle_;

    bool move();
};

