#include "Button.hpp"

AbstractButton::AbstractButton(const POINT& pos, const POINT& size, const Vector& fill_color, const Vector& text_color, func_t func) :
    pos_        (pos),
    size_       (size),
    fill_color_ (fill_color),
    text_color_ (text_color),
    status_     (0),
    func_       (func)
{}

bool BasicButton::pinched() {
    return false;//??? тут могла быть ваша функция
}

void BasicButton::pressed() {
    if (func_ != nullptr) func_();
}

BasicButton::BasicButton(const POINT& pos, const POINT& size, const Vector& fill_color, const Vector& text_color, std::string text, func_t func) :
    AbstractButton (pos, size, fill_color, text_color, func),
    text_          (text)
{}

void BasicButton::draw() {
    if (fill_color_ != -EVEC) {
        setColor    (VEC2RGB((fill_color_ * 0.8)));
        setFillColor(VEC2RGB((fill_color_ * (1 - status_ * 0.1))));

        rectangle(pos_.x, pos_.y, pos_.x + size_.x, pos_.y + size_.y);
    }

    if (text_color_ != -EVEC) {
        setColor(VEC2RGB(text_color_), 1);
    
        drawText(pos_.x, pos_.y, pos_.x + size_.x, pos_.y + size_.y, text_.c_str(), DT_CENTER | DT_VCENTER);
    }
}

bool BasicButton::mouse_on_button(const POINT& mouse_pos) {
    return (mouse_pos.x > pos_.x           &&
            mouse_pos.x < pos_.x + size_.x &&
            mouse_pos.y > pos_.y           &&
            mouse_pos.y < pos_.y + size_.y);
}

TextButton::TextButton(double* val, int bind, const POINT& pos, const POINT& size, const Vector& fill_color, const Vector& text_color, int minv, int maxv, int mult) :
    BasicButton(pos, size, fill_color, text_color),
    val_       (val),
    bind_      (bind),
    minv_      (minv),
    maxv_      (maxv),
    mult_      (mult)
{
    assert(mult_ != 0);

    if (val_ != nullptr) text_ = std::to_string(int (*val_ * mult_));
}

bool TextButton::pinched() {    
    POINT mouse1, mouse2;
    GetCursorPos(&mouse1);
    double shift = 0;

    bool res = false;

    while (GetAsyncKeyState(VK_LBUTTON)) { //можно реализовать лучше
        GetCursorPos(&mouse2);
        LONG offset = mouse2.x - mouse1.x;

        if (abs(offset) > 20) {
            res = true;

            drawCursor(IDC_SIZEWE);

            shift += (double) offset / 4000000;

            if (shift > 1) {
                double val = std::stod(text_) + 1;

                if (val >= minv_ && val <= maxv_) {
                    text_ = std::to_string((int) val);
                    draw();
                }

                shift -= 1;
            }

            if (shift < -1) {
                double val = std::stod(text_) - 1;

                if (val >= minv_ && val <= maxv_) {
                    text_ = std::to_string((int) val);
                    draw();
                }

                shift += 1;
            }
        }
    }

    double val = std::stod(text_);

    if (val_ != nullptr) {
        *val_ = val / mult_;
    }

    drawCursor(IDC_ARROW);

    return res;
}

void TextButton::pressed() {
    while (!GetAsyncKeyState(VK_RETURN) && !GetAsyncKeyState(VK_ESCAPE)) {
        for (int index = 48; index <= 57 && text_.length() < 6; ++index) {
            if (GetAsyncKeyState(index)) {
                if (text_[0] == '0') text_.erase(text_.begin());

                text_ += (char) index;
                draw();
                
                while (GetAsyncKeyState(index)) {}
            }
        }

        if (text_[0] == '0' && GetAsyncKeyState(189)) {
            text_ = '-';
            draw();

            while (GetAsyncKeyState(189)) {}
        }

        if (GetAsyncKeyState(VK_BACK) && !text_.empty()) {
            text_.pop_back();

            if (text_.empty()) text_ += '0';

            draw();

            while (GetAsyncKeyState(VK_BACK)) {}
        }

        if (GetAsyncKeyState(VK_LBUTTON) && !mouse_on_button(mousePos())) {
            while (GetAsyncKeyState(VK_BACK)) {}

            break;
        }
    }

    if (text_.length() == 1 && text_[0] == '-') {
        text_ = std::to_string((int) *val_ * mult_);

        draw();
        return;
    }

    double val = std::stod(text_);

    if (val < minv_ || val > maxv_) {
        val = std::min(std::max((int) val, minv_), maxv_);

        text_ = std::to_string((int) *val_ * mult_);

        draw();
    }

    if (val_ != nullptr) {
        *val_ = val / mult_;
    }
}

double* getParam(int id, Object* obj) {
    switch (id) {
    case posX:
        return &obj->center_.x_;

    case posY:
        return &obj->center_.y_;

    case posZ:
        return &obj->center_.z_;

    case rotX:
        return &obj->rotation_.x_;

    case rotY:
        return &obj->rotation_.y_;

    case rotZ:
        return &obj->rotation_.z_;

    case szX:
        return &obj->size_.x_;

    case szY:
        return &obj->size_.y_;

    case szZ:
        return &obj->size_.z_;

    case colX:
        return &obj->color_.x_;

    case colY:
        return &obj->color_.y_;
        
    case colZ:
        return &obj->color_.z_;

    default:
        break;
    }

    return nullptr;
}