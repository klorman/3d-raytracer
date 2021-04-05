#include "Window.hpp"
#include "TXLib.h" 
#include "Vector.hpp"

Window::Window(int width, int height) :
	width_(width),
	height_(height),
	Video_memory_(NULL)
{}

void Window::draw_pixel(Vector coords, Vector color_of_point) {
	RGBQUAD* pixel = &Video_memory_[(height_ - (int)coords.y_) * width_ + (int)coords.x_];
	pixel->rgbRed =   (BYTE) color_of_point.x_;
	pixel->rgbGreen = (BYTE) color_of_point.y_;
	pixel->rgbBlue =  (BYTE) color_of_point.z_;
}