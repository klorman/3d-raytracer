#pragma once

#include "TXLib.h"
#include "Vector.hpp"

class Textbox {
public:
    POINT pos_, size_;
    Vector fill_color_, text_color_;
};