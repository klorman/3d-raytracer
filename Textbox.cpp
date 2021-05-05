#include "Textbox.hpp"

Textbox::Textbox(const POINT& pos, const POINT& size, std::string text, const Vector& fill_color, const Vector& text_color) :
    wndPos_     (pos),
    fieldPos_   (pos),
    size_       (size),
    text_       (text),
    fill_color_ (fill_color),
    text_color_ (text_color)
{}

void Textbox::draw(HDC dc) {
    if (fill_color_ != -EVEC) {
        txSetColor    (VEC2RGB((fill_color_ * 0.8)), 1, dc);
        txSetFillColor(VEC2RGB(fill_color_), dc);
        txRectangle   (fieldPos_.x, fieldPos_.y, fieldPos_.x + size_.x, fieldPos_.y + size_.y, dc);
    }

    txSetColor (VEC2RGB(text_color_), 1, dc);
    
    txDrawText(fieldPos_.x, fieldPos_.y, fieldPos_.x + size_.x, fieldPos_.y + size_.y, text_.c_str(), DT_CENTER | DT_VCENTER, dc);
}