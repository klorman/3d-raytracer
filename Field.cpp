#include "Field.hpp"

Field::Field(bool visible, POINT pos, POINT size) :
    visible_      (visible),
    pos_          (pos),
    size_         (size),
    canvas_size_  (size),
    button_count_ (0),
    textbox_count_(0),
    buttons_      (std::vector<AbstractButton*>()),
    textboxes_    (std::vector<Textbox>()),
    canvas_       (NULL),
    scroll_       (false)
{}

Field::Field(const Field& field) :
    visible_       (field.visible_),
    pos_           (field.pos_),
    size_          (field.size_),
    canvas_size_   (field.canvas_size_),
    button_count_  (field.button_count_),
    textbox_count_ (field.textbox_count_),
    buttons_       (field.buttons_),
    textboxes_     (field.textboxes_),
    canvas_        (NULL),
    scroll_        (field.scroll_)
{}

Field::~Field() {
    txDeleteDC(canvas_);
}

void Field::addButton(AbstractButton* button) {
    button_count_++;

    buttons_.push_back(button);

    buttons_.back()->wndPos_.x += pos_.x;
    buttons_.back()->wndPos_.y += pos_.y;

    if (!scroll_ && (button->fieldPos_.y + button->size_.y > size_.y)) { // 
        scroll_ = true;                                                  // скорее всего это уже не понадобится
        size_.x -= 20;                                                   //
    }                                                                    //

    if (button->fieldPos_.y + button->size_.y > canvas_size_.y) {
        canvas_size_.y = button->fieldPos_.y + button->size_.y;
    }
}

void Field::addTextbox(const Textbox& textbox) {
    textbox_count_++;

    textboxes_.push_back(textbox);

    textboxes_.back().wndPos_.x += pos_.x;
    textboxes_.back().wndPos_.y += pos_.y;

    if (!scroll_ && (textbox.fieldPos_.y + textbox.size_.y > size_.y)) { //
        scroll_ = true;                                                  // скорее всего это уже не понадобится
        size_.x -= 20;                                                   //
    }                                                                    // 

    if (textbox.fieldPos_.y + textbox.size_.y > canvas_size_.y) {
        canvas_size_.y = textbox.fieldPos_.y + textbox.size_.y;
    }
}

void Field::draw() {
    txSetColor    (VEC2RGB((prop.INTERFACECOLOR * 0.9)), 1, canvas_);
    txSetFillColor(VEC2RGB(prop.INTERFACECOLOR), canvas_);

    txRectangle(0, 0, canvas_size_.x, canvas_size_.y, canvas_);

    for (int button = 0; button < button_count_; ++button) {
        buttons_[button]->draw(canvas_, false);
    }

    for (int textbox = 0; textbox < textbox_count_; ++textbox) {
        textboxes_[textbox].draw(canvas_);
    }
}

bool Field::mouse_on_field() {
    POINT mouse = mousePos();

    return (mouse.x > pos_.x && mouse.x < pos_.x + size_.x && mouse.y > pos_.y && mouse.y < pos_.y + size_.y) ? true : false;
}