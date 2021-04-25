#include "Field.hpp"

Field::Field(bool visible, POINT pos, POINT size, int button_count, int textbox_count, AbstractButton** buttons, Textbox* textboxes) :
    visible_      (visible),
    pos_          (pos),
    size_         (size),
    button_count_ (button_count),
    textbox_count_(textbox_count),
    buttons_      (buttons),
    textboxes_    (textboxes)
{
    for (int button = 0; button < button_count_; ++button) {
        buttons_[button]->pos_.x += pos_.x;
        buttons_[button]->pos_.y += pos_.y;
    }

    for (int textbox = 0; textbox < textbox_count_; ++textbox) {
        textboxes_[textbox].pos_.x += pos_.x;
        textboxes_[textbox].pos_.y += pos_.y;
    }
}

void Field::draw() {
    for (int button = 0; button < button_count_; ++button) {
        buttons_[button]->draw();
    }

    for (int textbox = 0; textbox < textbox_count_; ++textbox) {
        textboxes_[textbox].draw();
    }
}