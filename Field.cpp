#include "Field.hpp"

Field::Field(bool visible, POINT pos, POINT size) :
    visible_      (visible),
    pos_          (pos),
    size_         (size),
    button_count_ (0),
    textbox_count_(0),
    buttons_      (std::vector<AbstractButton*>()),
    textboxes_    (std::vector<Textbox>())
{}


void Field::addButton(AbstractButton* button) {
    button_count_++;

    buttons_.push_back(button);

    buttons_.back()->pos_.x += pos_.x;
    buttons_.back()->pos_.y += pos_.y;
}

void Field::addTextbox(const Textbox& textbox) {
    textbox_count_++;

    textboxes_.push_back(textbox);

    textboxes_.back().pos_.x += pos_.x;
    textboxes_.back().pos_.y += pos_.y;
}

void Field::draw() {
    for (int button = 0; button < button_count_; ++button) {
        buttons_[button]->draw();
    }

    for (int textbox = 0; textbox < textbox_count_; ++textbox) {
        textboxes_[textbox].draw();
    }
}