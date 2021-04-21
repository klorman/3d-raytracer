#include "Camera.hpp"
#include "TXLib.h"

bool Camera::move() {
    bool moved = false;

    double fps = txGetFPS();

    if (fps < 1) {
        fps = 1;
    }

    double a = 1 / fps;

    if (GetAsyncKeyState(VK_UP   )) { angle_.y_ -= a; moved = true; };
    if (GetAsyncKeyState(VK_DOWN )) { angle_.y_ += a; moved = true; };
    if (GetAsyncKeyState(VK_LEFT )) { angle_.x_ -= a; moved = true; }; 
    if (GetAsyncKeyState(VK_RIGHT)) { angle_.x_ += a; moved = true; };

    if (moved) dir_ = Vector {0,0,1}.rot(angle_);
    
    if (GetAsyncKeyState(   'A'  )) { pos_ -= Vector {  dir_.z_, 0, -dir_.x_ } * speed_ / fps; moved = true; };
    if (GetAsyncKeyState(   'D'  )) { pos_ -= Vector { -dir_.z_, 0,  dir_.x_ } * speed_ / fps; moved = true; };
    if (GetAsyncKeyState(   'W'  )) { pos_ += dir_ * speed_ / fps; moved = true; };
    if (GetAsyncKeyState(   'S'  )) { pos_ -= dir_ * speed_ / fps; moved = true; };
    if (GetAsyncKeyState(VK_SPACE)) { pos_ -= Vector { 0,  1, 0 } * speed_ / fps; moved = true; };
    if (GetAsyncKeyState(VK_SHIFT)) { pos_ -= Vector { 0, -1, 0 } * speed_ / fps; moved = true; };
    
    return moved;
}