#include "Window.hpp"

Interface::Interface(double bottom, double right) :
    bottom_size_ (bottom),
    right_size_  (right),
    button_count_(0),
    buttons_     (nullptr)
{}

void Interface::draw              (const Window& wnd) {
    txSetColor    (VEC2RGB((BACKGROUND * 0.9)), 1, wnd.dc_);
    txSetFillColor(VEC2RGB(BACKGROUND),            wnd.dc_);

    txRectangle(0, wnd.height_, wnd.width_, wnd.height_ + bottom_size_, wnd.dc_);
    txRectangle(wnd.width_, 0, wnd.width_ + right_size_, wnd.height_ + bottom_size_, wnd.dc_);

    for (int button = 0; button < button_count_; ++button) {
        buttons_[button]->draw(wnd.dc_);
    }
}

void Interface::update            (const Window& wnd, const POINT& mouse_pos) {
    if (mouse_on_interface(wnd, mouse_pos)) {
        HDC dc = wnd.dc_;
        
        for (int button = 0; button < button_count_; ++button) {
            bool mob = buttons_[button]->mouse_on_button(mouse_pos);
            int status = txMouseButtons();

            if (mob && status == 0) {
                buttons_[button]->status_ = 1;
                buttons_[button]->draw(dc);
            }

            if (mob && status == 1) {
                buttons_[button]->status_ = 2;
                buttons_[button]->draw(dc);
            }

            else if (buttons_[button]->status_ != 0 && !mob) {
                buttons_[button]->status_ = 0;
                buttons_[button]->draw(dc);
            }
        }
    }
}

bool Interface::mouse_on_interface(const Window& wnd, const POINT& mouse_pos) {
    return mouse_pos.x > wnd.width_ || mouse_pos.y > wnd.height_; 
}