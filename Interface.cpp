#include "Window.hpp"

Interface::Interface(LONG bottom, LONG right) :
    bottom_size_ (bottom),
    right_size_  (right),
    field_count_ (0),
    fields_      (nullptr)
{}

void Interface::draw(Window& wnd) {
    setColor    (VEC2RGB((BACKGROUND * 0.9)));
    setFillColor(VEC2RGB(BACKGROUND));

    rectangle(0,          wnd.height_, wnd.width_,               wnd.height_ + bottom_size_);
    rectangle(wnd.width_, 0,           wnd.width_ + right_size_, wnd.height_ + bottom_size_);

    for (int field = 0; field < field_count_; ++field) {
        if (fields_[field].visible_) fields_[field].draw();
    }
}

void Interface::update(Window& wnd, const POINT& mouse_pos) {
    if (mouse_on_interface(wnd, mouse_pos)) {        
        for (int field = 0; field < field_count_; ++field) {
            if (!fields_[field].visible_) continue;

            for (int button = 0; button < fields_[field].button_count_; ++button) {
                bool mob = fields_[field].buttons_[button]->mouse_on_button(mouse_pos);
                int mouse_button = txMouseButtons();

                if (fields_[field].buttons_[button]->status_ == 3) continue;

                if (mob && mouse_button == 0 && fields_[field].buttons_[button]->status_ == 0) {
                    fields_[field].buttons_[button]->status_ = 1;
                    fields_[field].buttons_[button]->draw();
                }

                if (mob && mouse_button == 1 && fields_[field].buttons_[button]->status_ != 2) {
                    fields_[field].buttons_[button]->status_ = 2;
                    if (fields_[field].buttons_[button]->pinched()) fields_[field].buttons_[button]->status_ = 1;
                    fields_[field].buttons_[button]->draw();
                }

                if (mob && mouse_button == 0 && fields_[field].buttons_[button]->status_ == 2) {
                    fields_[field].buttons_[button]->status_ = 1;
                    fields_[field].buttons_[button]->pressed();
                    fields_[field].buttons_[button]->draw();
                }

                else if (fields_[field].buttons_[button]->status_ != 0 && !mob) {
                    fields_[field].buttons_[button]->status_ = 0;
                    fields_[field].buttons_[button]->draw();
                }
            }
        }
    }
}

bool Interface::mouse_on_interface(const Window& wnd, const POINT& mouse_pos) {
    return mouse_pos.x > wnd.width_ || mouse_pos.y > wnd.height_; 
}