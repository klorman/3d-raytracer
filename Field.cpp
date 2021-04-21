#include "Field.hpp"

Field::Field(bool visible, int button_count, int textbox_count, AbstractButton** buttons, Textbox* textboxes) :
    visible_      (visible),
    button_count_ (button_count),
    textbox_count_(textbox_count),
    buttons_      (buttons),
    textboxes_    (textboxes)
{}

void Field::draw() {
    for (int button = 0; button < button_count_; ++button) {
        buttons_[button]->draw();
    }

    for (int textbox = 0; textbox < textbox_count_; ++textbox) {
        textboxes_[textbox].draw();
    }
}