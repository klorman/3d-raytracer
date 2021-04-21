#pragma once

#include "TXLib.h"
#include "Vector.hpp"
#include "Window.hpp"
#include <string>

typedef void (*func_t) ();

enum binding {posX, posY, posZ, rotX, rotY, rotZ, szX, szY, szZ, colX, colY, colZ};

class AbstractButton {
public:
    POINT pos_, size_;
    Vector fill_color_, text_color_;
    int status_;
    func_t func_;
    Object* obj_;
    std::string text_;

    AbstractButton(const POINT& pos, const POINT& size, const Vector& fill_color, const Vector& text_color, std::string text, func_t func);
    virtual ~AbstractButton() = default;

    virtual bool mouse_on_button(const POINT& mouse_pos) = 0;
    virtual void draw() = 0;
    virtual void pressed() = 0;

    AbstractButton(const AbstractButton&) = delete;
    AbstractButton& operator=(const AbstractButton&) = delete;
};

class BasicButton : public AbstractButton {
public:
    BasicButton(const POINT& pos, const POINT& size, const Vector& fill_color = EVEC * 255, const Vector& text_color = NULLVEC, std::string text = "", func_t func = nullptr);

    virtual bool mouse_on_button(const POINT& mouse_pos) override;
    virtual void draw() override;
    virtual void pressed() override;

    BasicButton(const BasicButton&) = delete;
    BasicButton& operator=(const BasicButton&) = delete;
};

class TextButton : public BasicButton {
public:
    int bind_;

    TextButton(int bind, const POINT& pos, const POINT& size, const Vector& fill_color, const Vector& text_color);

    virtual void pressed() override;
    
    TextButton(const TextButton&) = delete;
    TextButton& operator=(const TextButton&) = delete;
};

double* getParam(int id, Object* obj);