#pragma once

#include "Button.hpp"
#include "Textbox.hpp"

class AbstractButton;
class Textbox;
class Image;

class Field {
public:
    bool                         visible_;
    POINT                        pos_,
                                 size_;
    int                          button_count_, 
                                 textbox_count_;
    std::vector<AbstractButton*> buttons_;
    std::vector<Textbox>         textboxes_;
    HDC                          canvas_;

    Field(bool visible, POINT pos, POINT size);
    Field(const Field& field);
    ~Field();

    void addButton(AbstractButton* button);
    void addTextbox(const Textbox& textbox);
    void draw();

    Field& operator=(const Field&) = delete;
};