#pragma once

#include "Matrix.hpp"
#include "Window.hpp"

class Window;

class Camera {
public:
    double speed_;
    Vector pos_, dir_, angle_;
    POINT  mouse_;

    Camera(double speed, const Vector& pos, const Vector& dir, const Vector& angle);

    bool move(Window& wnd);
};