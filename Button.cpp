#include "Button.hpp"

AbstractButton::AbstractButton(const POINT& pos, const POINT& size, const Vector& fill_color, const Vector& text_color, func_t func) :
    pos_       (pos),
    size_      (size),
    fill_color_(fill_color),
    text_color_(text_color),
    status_    (0),
    func_      (func)
{}

void AbstractButton::pressed() {
    if (func_ != nullptr) func_();

    //status_ = 1;
    //draw(wnd.get_DC());
}

BasicButton::BasicButton(const POINT& pos, const POINT& size, const Vector& fill_color, const Vector& text_color, const char* text, func_t func) :
    AbstractButton(pos, size, fill_color, text_color, func),
    text_(text)
{}

bool BasicButton::mouse_on_button(const POINT& mouse_pos) {
    return (mouse_pos.x > pos_.x          &&
            mouse_pos.x < pos_.x + size_.x &&
            mouse_pos.y > pos_.y          &&
            mouse_pos.y < pos_.y + size_.y);
}

//void BasicButton::draw(HDC dc) {
//    txSetColor    (VEC2RGB((fill_color_ * 0.8)), 1, dc);
//    txSetFillColor(VEC2RGB((fill_color_ * (1 - status_ * 0.1))), dc);
//
//    txRectangle(pos_.x, pos_.y, pos_.x + size_.x, pos_.y + size_.y, dc);
//
//    txSetColor(VEC2RGB(text_color_), 1, dc);
//    
//    txDrawText(pos_.x, pos_.y, pos_.x + size_.x, pos_.y + size_.y, text_, DT_CENTER | DT_VCENTER, dc);
//}