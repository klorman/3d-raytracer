#include "Window.hpp"
#include "TXLib.h" 
#include "Vector.hpp"

Window::Window(int width, int height) :
	width_(width),
	height_(height)
{
	txCreateWindow(width_, height_);
	Video_memory_ = txVideoMemory();
}

void Window::draw_pixel(Vector coords, Vector color) {
	RGBQUAD* pixel = &Video_memory_[(height_ - 1 - (int)coords.y_) * width_ + (int)coords.x_];
	pixel->rgbRed   = (BYTE) color.x_;
	pixel->rgbGreen = (BYTE) color.y_;
	pixel->rgbBlue  = (BYTE) color.z_;
}