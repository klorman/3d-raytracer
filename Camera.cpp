#include "Camera.hpp"

Camera::Camera() :
    speed_     (0),
    pos_       (NULLVEC),
    dir_       (NULLVEC),
    angle_     (NULLVEC),
    mouse_     ({0, 0})
{}

Camera::Camera(double speed, const Vector& pos, const Vector& dir, const Vector& angle) :
    speed_     (speed),
    pos_       (pos),
    dir_       (dir),
    angle_     (angle),
    mouse_     ({0, 0})
{}

bool Camera::move(Window& wnd) {
    bool moved = false;
    static bool rotWithMouse = false;
    static std::vector<Camera> templates(10);

    if (GetAsyncKeyState(VK_LCONTROL) & 0x8000) {
        for (int index = 48; index <= 57; ++index) {
            if (GetAsyncKeyState(index) & 0x8000) templates[index - 48] = *this;
        }
    }

    else {
        for (int index = 48; index <= 57; ++index) {
            if ((GetAsyncKeyState(index) & 0x8000) && templates[index - 48].dir_ != NULLVEC) {*this = templates[index - 48]; moved = true;}
        }
    }

    double fps = txGetFPS();

    if (fps < 1) {
        fps = 1;
    }

    double a = 1 / fps;

    POINT mouse_pos = mousePos();

    if ((GetAsyncKeyState(VK_RBUTTON) & 0x8000) && ((mouse_pos.x < wnd.width_ && mouse_pos.y < wnd.height_) || rotWithMouse)) {
        if (mouse_.x == 0 && mouse_.y == 0) {
            GetCursorPos(&mouse_);

            drawCursor(NULL);

            rotWithMouse = true;

            return true;
        }

        POINT pos;
        GetCursorPos(&pos);

        Vector offset = {double (pos.x - mouse_.x), double (pos.y - mouse_.y), 0};

        angle_ += offset / 512;
        moved = true;

        SetCursorPos(mouse_.x, mouse_.y);
    }

    else if (mouse_.x != 0 || mouse_.y != 0) {
        mouse_ = {0, 0};
        rotWithMouse = false;

        drawCursor(LoadCursor(0, IDC_ARROW));
    }

    if (GetAsyncKeyState(VK_UP   ) & 0x8000) { angle_.y_ -= a; moved = true; };
    if (GetAsyncKeyState(VK_DOWN ) & 0x8000) { angle_.y_ += a; moved = true; };
    if (GetAsyncKeyState(VK_LEFT ) & 0x8000) { angle_.x_ -= a; moved = true; }; 
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000) { angle_.x_ += a; moved = true; };

    if (angle_.x_ > PIx2) angle_.x_ -= PIx2;
    if (angle_.x_ < 0   ) angle_.x_ += PIx2;
    angle_.y_ = std::max(std::min(angle_.y_, txPI / 2), -txPI / 2); 

    if (moved) dir_ = Vector {0,0,1}.rot(angle_);
    
    if (GetAsyncKeyState(   'A'  ) & 0x8000) { pos_ -= Vector {  dir_.z_, 0, -dir_.x_ }.norm() * speed_ / fps; moved = true; };
    if (GetAsyncKeyState(   'D'  ) & 0x8000) { pos_ -= Vector { -dir_.z_, 0,  dir_.x_ }.norm() * speed_ / fps; moved = true; };
    if (GetAsyncKeyState(   'W'  ) & 0x8000) { pos_ += dir_ * speed_ / fps;                                    moved = true; };
    if (GetAsyncKeyState(   'S'  ) & 0x8000) { pos_ -= dir_ * speed_ / fps;                                    moved = true; };
    if (GetAsyncKeyState(VK_SPACE) & 0x8000) { pos_ -= Vector { 0,  1, 0 } * speed_ / fps;                     moved = true; };
    if (GetAsyncKeyState(VK_SHIFT) & 0x8000) { pos_ -= Vector { 0, -1, 0 } * speed_ / fps;                     moved = true; };
    
    return moved;
}