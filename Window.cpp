#include "Window.hpp"
#include "TXLib.h" 

Window::Window(int width, int height) :
	width_(width),
	height_(height)
{
	txCreateWindow(width_, height_);
	Video_memory_ = txVideoMemory();
}

Window::~Window() {
	txDisableAutoPause();
	//txDestroyWindow();
}

void Window::draw_pixel(Vector coords, Vector color) {
	RGBQUAD* pixel = &Video_memory_[(height_ - 1 - (int)coords.y_) * width_ + (int)coords.x_];
	pixel->rgbRed   = (BYTE) color.x_;
	pixel->rgbGreen = (BYTE) color.y_;
	pixel->rgbBlue  = (BYTE) color.z_;
}

void Window::update(Raytracer rt, Camera cam) {
	txBegin();
    for (double x = 0; x < width_; ++x) {
        for (double y = 0; y < height_; ++y) {
			Vector px = {x - width_ / 2, y - height_ / 2, 0};
			Vector offset = px - cam.dir_ * (px ^ cam.dir_);
			Vector dir = (cam.dir_ * 1000 + offset).norm();
            draw_pixel({x,y,0}, rt.color({cam.pos_, dir}));
        }
    }
	txEnd();
}