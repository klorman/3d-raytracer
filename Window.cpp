#include "Window.hpp"
#include "TXLib.h" 
#include "Vector.hpp"

Window::Window(int width, int height) :
	width_(width),
	height_(height),
	Video_memory_(NULL)
{}

void Window::draw_pixel(Vector coords, Vector color) {
	//std::cout << coords.x_ << " " << coords.y_ << std::endl;
	RGBQUAD* pixel = &Video_memory_[(height_ - (int)coords.y_) * width_ + (int)coords.x_];
	pixel->rgbRed   = (BYTE) color.x_;
	pixel->rgbGreen = (BYTE) color.y_;
	pixel->rgbBlue  = (BYTE) color.z_;
}