#pragma once

#include "Button.hpp"
#include "Textbox.hpp"

class AbstractButton;
class Textbox;

class Field {
public:
    bool             visible_;
    POINT            pos_,
                     size_;
    int              button_count_, 
                     textbox_count_;
    AbstractButton** buttons_;
    Textbox*         textboxes_;

    Field(bool visible, POINT pos, POINT size, int button_count, int textbox_count, AbstractButton** buttons, Textbox* textboxes);

    void draw();
};