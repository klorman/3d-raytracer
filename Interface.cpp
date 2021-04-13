#include "Window.hpp"

Interface::Interface(LONG bottom, LONG right) :
    bottom_size_ (bottom),
    right_size_  (right),
    button_count_(0),
    buttons_     (nullptr)
{}

//void Interface::draw(Window& wnd) {
//    txSetColor    (VEC2RGB((BACKGROUND * 0.9)), 1, wnd.get_DC());
//    txSetFillColor(VEC2RGB(BACKGROUND),            wnd.get_DC());
//
//    txRectangle(0,          wnd.height_, wnd.width_,               wnd.height_ + bottom_size_, wnd.get_DC());
//    txRectangle(wnd.width_, 0,           wnd.width_ + right_size_, wnd.height_ + bottom_size_, wnd.get_DC());
//
//    for (int button = 0; button < button_count_; ++button) {
//        buttons_[button]->draw(wnd.get_DC());
//    }
//}

void Interface::update(Window& wnd, const POINT& mouse_pos) {
    if (mouse_on_interface(wnd, mouse_pos)) {        
        for (int button = 0; button < button_count_; ++button) {
            bool mob = buttons_[button]->mouse_on_button(mouse_pos);
            int mouse_button = txMouseButtons();

            if (mob && mouse_button == 0 && buttons_[button]->status_ == 0) {
                buttons_[button]->status_ = 1;
                buttons_[button]->draw(wnd.get_DC());
            }

            if (mob && mouse_button == 1 && buttons_[button]->status_ != 2) {
                buttons_[button]->status_ = 2;
                buttons_[button]->draw(wnd.get_DC());
            }

            if (mob && mouse_button == 0 && buttons_[button]->status_ == 2) {
                buttons_[button]->status_ = 1;
                buttons_[button]->draw(wnd.get_DC());
                buttons_[button]->pressed();
            }

            else if (buttons_[button]->status_ != 0 && !mob) {
                buttons_[button]->status_ = 0;
                buttons_[button]->draw(wnd.get_DC());
            }
        }
    }
}

bool Interface::mouse_on_interface(const Window& wnd, const POINT& mouse_pos) {
    return mouse_pos.x > wnd.width_ || mouse_pos.y > wnd.height_; 
}