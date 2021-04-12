#pragma once

#include "TXLib.h"
#include "Vector.hpp"

class AbstractButton {
public:
    POINT pos_, size_;
    Vector fill_color_, text_color_;
    int status_;

    AbstractButton(const POINT& pos, const POINT& size, const Vector& fill_color = EVEC * 255, const Vector& text_color = NULLVEC);
    virtual ~AbstractButton() = default;

    virtual bool mouse_on_button(const POINT& mouse_pos) = 0;
    virtual void draw(HDC dc) = 0;
};

class BasicButton : public AbstractButton {
public:
    const char* text_;

    BasicButton(const POINT& pos, const POINT& size, const Vector& fill_color = EVEC * 255, const Vector& text_color = NULLVEC, const char* text = "");

    virtual bool mouse_on_button(const POINT& mouse_pos) override;
    virtual void draw(HDC dc) override;

    BasicButton(const BasicButton&) = delete;
    BasicButton& operator=(const BasicButton&) = delete;
};