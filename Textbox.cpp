#include "Textbox.hpp"

Textbox::Textbox(const POINT& pos, const POINT& size, std::string text, const Vector& fill_color, const Vector& text_color) :
    pos_(pos),
    size_(size),
    text_(text),
    fill_color_(fill_color),
    text_color_(text_color)
{}

void Textbox::draw() {
    setColor    (VEC2RGB((fill_color_ * 0.8)));
    setFillColor(VEC2RGB(fill_color_));
    rectangle   (pos_.x, pos_.y, pos_.x + size_.x, pos_.y + size_.y);
    setColor    (VEC2RGB(text_color_));
    
    drawText(pos_.x, pos_.y, pos_.x + size_.x, pos_.y + size_.y, text_.c_str(), DT_CENTER | DT_VCENTER);
}