#include "Window.hpp"

Interface::Interface(LONG bottom, LONG right) :
    bottom_size_ (bottom),
    right_size_  (right),
    field_count_ (0),
    fields_      (std::vector<Field>())
{}

void Interface::addField(bool visible, POINT pos, POINT size) {
    field_count_++;

    fields_.push_back({visible, pos, size});
}

void Interface::draw() {
    for (int field = 0; field < field_count_; ++field) {
        if (fields_[field].visible_) {
            fields_[field].draw();

            copyToWnd(fields_[field].canvas_, fields_[field].pos_.x, fields_[field].pos_.y, fields_[field].size_.x, fields_[field].size_.y);
        }
    }
}

void Interface::update(Window& wnd, const POINT& mouse_pos) {
    if (mouse_on_interface(wnd, mouse_pos)) {        
        for (int field = 0; field < field_count_; ++field) {
            if (!fields_[field].visible_) continue;

            //copyToWnd(fields_[field].canvas_, fields_[field].pos_.x, fields_[field].pos_.y, fields_[field].size_.x, fields_[field].size_.y);

            for (int button = 0; button < fields_[field].button_count_; ++button) {
                bool mob = fields_[field].buttons_[button]->mouse_on_button(mouse_pos);
                int mouse_button = txMouseButtons();

                if (fields_[field].buttons_[button]->status_ == 3) continue;

                if (mob && mouse_button == 0 && fields_[field].buttons_[button]->status_ == 0) {
                    fields_[field].buttons_[button]->status_ = 1;
                    fields_[field].buttons_[button]->draw(fields_[field].canvas_);
                }

                if (mob && mouse_button == 1 && fields_[field].buttons_[button]->status_ != 2) {
                    fields_[field].buttons_[button]->status_ = 2;
                    if (fields_[field].buttons_[button]->pinched(fields_[field].canvas_)) fields_[field].buttons_[button]->status_ = 1;
                    fields_[field].buttons_[button]->draw(fields_[field].canvas_);
                }

                if (mob && mouse_button == 0 && fields_[field].buttons_[button]->status_ == 2) {
                    fields_[field].buttons_[button]->status_ = 1;
                    fields_[field].buttons_[button]->pressed(fields_[field].canvas_);
                    if (fields_[field].visible_) fields_[field].buttons_[button]->draw(fields_[field].canvas_);
                }

                else if (fields_[field].buttons_[button]->status_ != 0 && !mob) {
                    fields_[field].buttons_[button]->status_ = 0;
                    fields_[field].buttons_[button]->draw(fields_[field].canvas_);
                }
            }
        }
    }
}

bool Interface::mouse_on_interface(const Window& wnd, const POINT& mouse_pos) {
    return mouse_pos.x > wnd.width_ || mouse_pos.y > wnd.height_; 
}