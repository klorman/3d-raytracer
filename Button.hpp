#pragma once

#include "TXLib.h"
#include "Vector.hpp"
#include "Window.hpp"

typedef void (*func_t) ();

class AbstractButton {
public:
    POINT pos_, size_;
    Vector fill_color_, text_color_;
    int status_;
    func_t func_;

    AbstractButton(const POINT& pos, const POINT& size, const Vector& fill_color, const Vector& text_color, func_t func);
    virtual ~AbstractButton() = default;

    virtual bool mouse_on_button(const POINT& mouse_pos) = 0;
    virtual void draw() = 0;

    void pressed();
};

class BasicButton : public AbstractButton {
public:
    const char* text_;

    BasicButton(const POINT& pos, const POINT& size, const Vector& fill_color = EVEC * 255, const Vector& text_color = NULLVEC, const char* text = "", func_t func = nullptr);

    virtual bool mouse_on_button(const POINT& mouse_pos) override;
    virtual void draw() override;

    BasicButton(const BasicButton&) = delete;
    BasicButton& operator=(const BasicButton&) = delete;
};

class TextButton : public BasicButton {
public:

};