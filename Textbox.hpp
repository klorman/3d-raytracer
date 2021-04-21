#pragma once

#include "TXLib.h"
#include "Vector.hpp"
#include "Window.hpp"

#include <string>

class Textbox {
public:
    POINT pos_, size_;
    std::string text_;
    Vector fill_color_, text_color_;
    
    Textbox(const POINT& pos, const POINT& size, std::string text = "", const Vector& fill_color = EVEC * 255, const Vector& text_color = NULLVEC);

    void draw();
};