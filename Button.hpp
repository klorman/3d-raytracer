#pragma once

#include "TXLib.h"
#include "Vector.hpp"
#include "Window.hpp"
#include <string>

typedef void (*func_t) ();

enum binding {posX, posY, posZ, rotX, rotY, rotZ, szX, szY, szZ, colX, colY, colZ, matRefl, matRefr, matTr, matRough};

class AbstractButton {
public:
    POINT wndPos_, fieldPos_, size_;
    POINT fieldCoords_, fieldSize_;
    Vector fill_color_, text_color_;
    int status_;
    func_t func_, pinched_func_;    

    AbstractButton(const POINT& pos, const POINT& size, const Vector& fill_color, const Vector& text_color, func_t func, func_t pinched_func);
    virtual ~AbstractButton() = default;

    virtual bool mouse_on_button(const POINT& mouse_pos) = 0;
    virtual void draw   (HDC dc, bool needToCopy = true) = 0;
    virtual bool pinched(HDC dc) = 0;
    virtual void pressed(HDC dc) = 0;

    AbstractButton(const AbstractButton&) = delete;
    AbstractButton& operator=(const AbstractButton&) = delete;
};

class BasicButton : public AbstractButton {
public:
    std::string text_;

    BasicButton(const POINT& pos, const POINT& size, const Vector& fill_color = EVEC * 255, const Vector& text_color = NULLVEC, std::string text = "", func_t func = nullptr, func_t pinched_func = nullptr);

    virtual bool mouse_on_button(const POINT& mouse_pos) override;
    virtual void draw   (HDC dc, bool needToCopy = true) override;
    virtual bool pinched(HDC dc) override;
    virtual void pressed(HDC dc) override;

    BasicButton(const BasicButton&) = delete;
    BasicButton& operator=(const BasicButton&) = delete;
};

class TextButton : public BasicButton {
public:
    double* val_;
    int bind_;
    int minv_, maxv_, mult_;

    TextButton(double* val_, int bind, const POINT& pos, const POINT& size, const Vector& fill_color, const Vector& text_color, int minv_ = -INF, int maxv_ = INF, int mult = 1);

    virtual bool pinched(HDC dc) override;
    virtual void pressed(HDC dc) override;
    
    TextButton(const TextButton&) = delete;
    TextButton& operator=(const TextButton&) = delete;
};

double* getParam(int id, Object* obj);