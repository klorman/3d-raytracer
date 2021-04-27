#include "Image.hpp"

Image::Image(const POINT& pos, const POINT& size) :
    pos_   (pos),
    size_  (size)
{
    image_ = txCreateCompatibleDC(size_.x, size_.y);
}

Image::~Image() {

}

void Image::createObjectImage(Object* object) {
    
}