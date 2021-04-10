#include "Camera.hpp"
#include "TXLib.h"

void Camera::move() {
    double fps = txGetFPS();

    if (fps < 1) {
        return;
    }

    double a = 1 / fps;

    //if (GetAsyncKeyState(VK_UP   )) dir_ = Vector ({dir_.x_, dir_.y_*cos(-a) + dir_.z_*sin(-a), -dir_.y_*sin(-a) + dir_.z_*cos(-a)}).norm();
    //if (GetAsyncKeyState(VK_DOWN )) dir_ = Vector ({dir_.x_, dir_.y_*cos( a) + dir_.z_*sin( a), -dir_.y_*sin( a) + dir_.z_*cos( a)}).norm();
    if (GetAsyncKeyState(VK_LEFT )) dir_ = Vector ({dir_.x_*cos( a) - dir_.z_*sin( a), dir_.y_,  dir_.x_*sin( a) + dir_.z_*cos( a)}).norm(); 
    if (GetAsyncKeyState(VK_RIGHT)) dir_ = Vector ({dir_.x_*cos(-a) - dir_.z_*sin(-a), dir_.y_,  dir_.x_*sin(-a) + dir_.z_*cos(-a)}).norm();

    if (GetAsyncKeyState(   'A'  )) pos_ -= Vector {  dir_.z_, dir_.y_, -dir_.x_ } * speed_ / fps;
    if (GetAsyncKeyState(   'D'  )) pos_ -= Vector { -dir_.z_, dir_.y_,  dir_.x_ } * speed_ / fps;
    if (GetAsyncKeyState(   'W'  )) pos_ += dir_ * speed_ / fps;
    if (GetAsyncKeyState(   'S'  )) pos_ -= dir_ * speed_ / fps;
    if (GetAsyncKeyState(VK_SPACE)) pos_ -= Vector { 0,  1, 0 } * speed_ / fps;
    if (GetAsyncKeyState(VK_SHIFT)) pos_ -= Vector { 0, -1, 0 } * speed_ / fps;
    
}