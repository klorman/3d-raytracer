#include "Camera.hpp"

Camera::Camera(double speed, const Vector& pos, const Vector& dir, const Vector& angle) :
    speed_ (speed),
    pos_   (pos),
    dir_   (dir),
    angle_ (angle),
    mouse_ ({0, 0})
{}

bool Camera::move(Window& wnd) {
    bool moved = false;

    double fps = txGetFPS();

    if (fps < 1) {
        fps = 1;
    }

    double a = 1 / fps;

    POINT mouse_pos = mousePos();

    if (GetAsyncKeyState(VK_RBUTTON) && mouse_pos.x < wnd.width_ && mouse_pos.y < wnd.height_) {
        if (mouse_.x == 0 && mouse_.y == 0) {
            GetCursorPos(&mouse_);

            ShowCursor(false);

            return true;
        }

        POINT pos;
        GetCursorPos(&pos);

        Vector offset = {double (pos.x - mouse_.x), double (pos.y - mouse_.y), 0};

        angle_ += offset / 100;
        moved = true;

        SetCursorPos(mouse_.x, mouse_.y);
    }

    else if (mouse_.x != 0 || mouse_.y != 0) {
        mouse_ = {0, 0};

        ShowCursor(true);
    }

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