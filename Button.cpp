#include "Button.hpp"

AbstractButton::AbstractButton(const POINT& pos, const POINT& size, const Vector& fill_color, const Vector& text_color, func_t func, func_t pinched_func) :
    wndPos_       (pos),
    fieldPos_     (pos),
    size_         (size),
    fieldCoords_  ({0, 0}),
    fieldSize_    ({0, 0}),
    fill_color_   (fill_color),
    text_color_   (text_color),
    status_       (0),
    func_         (func),
    pinched_func_ (pinched_func)
{}

bool BasicButton::pinched(HDC dc) {
    (void) dc;

    if (pinched_func_ != nullptr) {
        status_ = 1;

        pinched_func_();

        return true;
    }

    return false;
}

void BasicButton::pressed(HDC dc) {
    (void) dc;
    if (func_ != nullptr) func_();
}

BasicButton::BasicButton(const POINT& pos, const POINT& size, const Vector& fill_color, const Vector& text_color, std::string text, func_t func, func_t pinched_func) :
    AbstractButton (pos, size, fill_color, text_color, func, pinched_func),
    text_          (text)
{}

void BasicButton::draw(HDC dc, bool needToCopy) {
    if (fill_color_ != -EVEC) {
        txSetColor    (VEC2RGB((fill_color_ * 0.8)), 1, dc);
        txSetFillColor(VEC2RGB((fill_color_ * (1 - status_ * 0.1))), dc);

        txRectangle(fieldPos_.x, fieldPos_.y, fieldPos_.x + size_.x, fieldPos_.y + size_.y, dc);
    }

    if (text_color_ != -EVEC) {
        txSetColor(VEC2RGB(text_color_), 1, dc);
    
        txDrawText(fieldPos_.x, fieldPos_.y, fieldPos_.x + size_.x, fieldPos_.y + size_.y, text_.c_str(), DT_CENTER | DT_VCENTER, dc);
        //txDrawText(fieldPos_.x + 16, fieldPos_.y + 5, fieldPos_.x + 16 + size_.x, fieldPos_.y + 5 + size_.y, text_.c_str(), DT_CENTER | DT_VCENTER, dc);
    }

    if (needToCopy) {
        int upperOffset = wndPos_.y - fieldCoords_.y,
            lowerOffset = wndPos_.y + size_.y - fieldCoords_.y - fieldSize_.y;
        if (upperOffset > 0) upperOffset = 0;
        if (lowerOffset < 0) lowerOffset = 0;

        copyToWnd(dc, 
                  wndPos_.x, 
                  wndPos_.y - upperOffset, 
                  size_.x,
                  size_.y - upperOffset - lowerOffset, 
                  fieldPos_.x, 
                  fieldPos_.y - upperOffset);
    }

    //if (needToCopy) copyToWnd(dc, wndPos_.x, wndPos_.y, size_.x, size_.y, fieldPos_.x, fieldPos_.y);
}

bool BasicButton::mouse_on_button(const POINT& mouse_pos) {
    return (mouse_pos.x > wndPos_.x           &&
            mouse_pos.x < wndPos_.x + size_.x &&
            mouse_pos.y > wndPos_.y           &&
            mouse_pos.y < wndPos_.y + size_.y);
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

bool TextButton::pinched(HDC dc) {    
    POINT mouse1, mouse2;
    GetCursorPos(&mouse1);
    double shift = 0;

    bool res = false;

    while (GetAsyncKeyState(VK_LBUTTON) & 0x8000) { //можно реализовать лучше
        GetCursorPos(&mouse2);
        LONG offset = mouse2.x - mouse1.x;

        if (abs(offset) > 20) {
            res = true;

            drawCursor(LoadCursor(0, IDC_SIZEWE));

            shift += (double) offset / 4000000;

            if (shift > 1) {
                double val = std::stod(text_) + 1;

                if (val >= minv_ && val <= maxv_) {
                    text_ = std::to_string((int) val);
                    draw(dc);
                }

                shift -= 1;
            }

            if (shift < -1) {
                double val = std::stod(text_) - 1;

                if (val >= minv_ && val <= maxv_) {
                    text_ = std::to_string((int) val);
                    draw(dc);
                }

                shift += 1;
            }
        }
    }

    double val = std::stod(text_);

    if (val_ != nullptr) {
        *val_ = val / mult_;
    }

    drawCursor(LoadCursor(0, IDC_ARROW));

    return res;
}

void TextButton::pressed(HDC dc) {
    while (!GetAsyncKeyState(VK_RETURN) && !GetAsyncKeyState(VK_ESCAPE)) {
        for (int index = 48; index <= 57 && text_.length() < 6; ++index) {
            if (GetAsyncKeyState(index) & 0x8000) {
                if (text_[0] == '0') text_.erase(text_.begin());

                text_ += (char) index;
                draw(dc);
                
                while (GetAsyncKeyState(index)) {}
            }
        }

        if (text_[0] == '0' && GetAsyncKeyState(189) & 0x8000) {
            text_ = '-';
            draw(dc);

            while (GetAsyncKeyState(189)) {}
        }

        if ((GetAsyncKeyState(VK_BACK) & 0x8000) && !text_.empty()) {
            text_.pop_back();

            if (text_.empty()) text_ += '0';

            draw(dc);

            while (GetAsyncKeyState(VK_BACK)) {}
        }

        if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) && !mouse_on_button(mousePos())) {
            //while (GetAsyncKeyState(VK_LBUTTON)) {}

            break;
        }
    }

    if (text_.length() == 1 && text_[0] == '-') {
        text_ = std::to_string((int) *val_ * mult_);

        draw(dc);

        return;
    }

    double val = std::stod(text_);

    if (val < minv_ || val > maxv_) {
        val = std::min(std::max((int) val, minv_), maxv_);

        text_ = std::to_string((int) val);

        draw(dc);
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
    
    case matRefl:
        return &obj->mat_.reflection;

    case matRefr:
        return &obj->mat_.n;

    case matTr:
         return &obj->mat_.transparency;
    
    case matRough:
        return &obj->mat_.roughness;

    default:
        break;
    }

    return nullptr;
}