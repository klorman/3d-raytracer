#pragma once

#include "Button.hpp"
#include "Textbox.hpp"

class Field {
public:
    bool             visible_;
    int              button_count_, 
                     textbox_count_;
    AbstractButton** buttons_;
    Textbox*         textboxes_;

    void draw();
};