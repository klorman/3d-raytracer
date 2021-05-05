#include "Field.hpp"

Field::Field(bool visible, POINT pos, POINT size) :
    visible_      (visible),
    pos_          (pos),
    size_         (size),
    button_count_ (0),
    textbox_count_(0),
    buttons_      (std::vector<AbstractButton*>()),
    textboxes_    (std::vector<Textbox>()),
    canvas_       (txCreateCompatibleDC(size.x, size.y)),
    scroll_       (false)
{}

Field::Field(const Field& field) :
    visible_       (field.visible_),
    pos_           (field.pos_),
    size_          (field.size_),
    button_count_  (field.button_count_),
    textbox_count_ (field.textbox_count_),
    buttons_       (field.buttons_),
    textboxes_     (field.textboxes_),
    canvas_        (txCreateCompatibleDC(field.size_.x, field.size_.y)),
    scroll_        (field.scroll_)
{
    txBitBlt(canvas_, 0, 0, size_.x, size_.y, field.canvas_);

    txSelectFont("Consolas", 20, false, FW_BOLD, false, false, false, 0, canvas_);
}

Field::~Field() {
    txDeleteDC(canvas_);
}

void Field::addButton(AbstractButton* button) {
    button_count_++;

    buttons_.push_back(button);

    buttons_.back()->wndPos_.x += pos_.x;
    buttons_.back()->wndPos_.y += pos_.y;

    if (!scroll_ && (button->fieldPos_.y + button->size_.y > size_.y)) {
        scroll_ = true;
        size_.x -= 20;
    }
}

void Field::addTextbox(const Textbox& textbox) {
    textbox_count_++;

    textboxes_.push_back(textbox);

    textboxes_.back().wndPos_.x += pos_.x;
    textboxes_.back().wndPos_.y += pos_.y;

    if (!scroll_ && (textbox.fieldPos_.y + textbox.size_.y > size_.y)) {
        scroll_ = true;
        size_.x -= 20;
    }
}

void Field::draw() {
    txSetColor    (VEC2RGB((prop.INTERFACECOLOR * 0.9)), 1, canvas_);
    txSetFillColor(VEC2RGB(prop.INTERFACECOLOR), canvas_);

    txRectangle(0, 0, size_.x, size_.y, canvas_);

    for (int button = 0; button < button_count_; ++button) {
        buttons_[button]->draw(canvas_);
    }

    for (int textbox = 0; textbox < textbox_count_; ++textbox) {
        textboxes_[textbox].draw(canvas_);
    }
}