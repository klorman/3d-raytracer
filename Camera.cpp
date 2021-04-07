#include "Camera.hpp"
#include "TXLib.h"

void Camera::move() {
    const double a = 0.1; //не хочу сейчас заморачиваться с векторами
    //if (GetAsyncKeyState(VK_UP   )) dir_ = Vector ({dir_.x_, dir_.y_*cos(-a) + dir_.z_*sin(-a), -dir_.y_*sin(-a) + dir_.z_*cos(-a)}).norm();
    //if (GetAsyncKeyState(VK_DOWN )) dir_ = Vector ({dir_.x_, dir_.y_*cos( a) + dir_.z_*sin( a), -dir_.y_*sin( a) + dir_.z_*cos( a)}).norm();
    if (GetAsyncKeyState(VK_LEFT )) dir_ = Vector ({dir_.x_*cos( a) - dir_.z_*sin( a), dir_.y_,  dir_.x_*sin( a) + dir_.z_*cos( a)}).norm(); 
    if (GetAsyncKeyState(VK_RIGHT)) dir_ = Vector ({dir_.x_*cos(-a) - dir_.z_*sin(-a), dir_.y_,  dir_.x_*sin(-a) + dir_.z_*cos(-a)}).norm();


    if (GetAsyncKeyState(   'A'  )) pos_ -= Vector {  dir_.z_, dir_.y_, -dir_.x_ } * 10;
    if (GetAsyncKeyState(   'D'  )) pos_ -= Vector { -dir_.z_, dir_.y_,  dir_.x_ } * 10;
    if (GetAsyncKeyState(   'W'  )) pos_ += dir_ * 10;
    if (GetAsyncKeyState(   'S'  )) pos_ -= dir_ * 10;
    if (GetAsyncKeyState(VK_SPACE)) pos_ -= Vector { 0,  1, 0 } * 10;
    if (GetAsyncKeyState(VK_SHIFT)) pos_ -= Vector { 0, -1, 0 } * 10;
    
}