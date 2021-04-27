#pragma once

#include "Button.hpp"
#include "Textbox.hpp"
#include "Image.hpp"

class AbstractButton;
class Textbox;
class Image;

class Field {
public:
    bool                         visible_;
    POINT                        pos_,
                                 size_;
    int                          button_count_, 
                                 textbox_count_,
                                 image_count_;
    std::vector<AbstractButton*> buttons_;
    std::vector<Textbox>         textboxes_;
    std::vector<Image>           images_;

    Field(bool visible, POINT pos, POINT size);

    void addButton(AbstractButton* button);
    void addTextbox(const Textbox& textbox);
    void addImage(const Image& image);
    void draw();
};