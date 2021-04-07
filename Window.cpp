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
			double  proj1 = sqrt(cam.dir_.y_*cam.dir_.y_ + cam.dir_.z_*cam.dir_.z_),
					proj2 = sqrt(cam.dir_.z_*cam.dir_.z_ + cam.dir_.x_*cam.dir_.x_);

			//double cos1 = 0, sin1 = 0, cos2 = 0, sin2 = 0;
			//if (proj1 != 0) {
			//	cos1 = cam.dir_.y_ / proj1,
			//	sin1 = cam.dir_.z_ / proj1;
			//	px = {px.x_, px.y_*cos1 - px.z_*sin1, px.y_*sin1 + px.z_*cos1};
			//}			

			if (proj2 != 0) {
				double	cos2 = cam.dir_.z_ / proj2,
						sin2 = cam.dir_.x_ / proj2;
				px = {px.x_*cos2 + px.z_*sin2, px.y_, -px.x_*sin2 + px.z_*cos2};
			}

			Vector dir = (cam.dir_ * 1000 + px).norm();
            draw_pixel({x,y,0}, rt.color({cam.pos_, dir, 1}));
        }
    }
	txEnd();
}