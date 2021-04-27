#pragma once

#include "TXLib.h"
#include "Window.hpp"

class Image {
public:
    POINT pos_, size_;
    HDC image_;

    Image(const POINT& pos, const POINT& size);
    ~Image();

    void createObjectImage(Object* object);
};