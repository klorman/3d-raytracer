#include "Window.hpp"

#include <omp.h>

Window::Window(int width, int height) :
	width_(width),
	height_(height),
	Video_memory_(nullptr)
{
	txCreateWindow(width_, height_);
	Video_memory_ = txVideoMemory();

	_txCursorBlinkInterval = 1;
	_txWindowUpdateInterval = 60;
}

Window::~Window() {
	txDisableAutoPause();
}

void Window::draw_pixel(const Vector& coords, const Vector& color) {
	RGBQUAD* pixel = &Video_memory_[(height_ - 1 - (int)coords.y_) * width_ + (int)coords.x_];
	pixel->rgbRed   = (BYTE) color.x_;
	pixel->rgbGreen = (BYTE) color.y_;
	pixel->rgbBlue  = (BYTE) color.z_;
}

void Window::update(Raytracer& rt, const Camera& cam) {
	txBegin();

	const int num_threads = 16;
	omp_set_num_threads(num_threads);
	
	#pragma omp parallel num_threads(num_threads)
	{
		int thread = omp_get_thread_num();

		POINT start = { width_ * thread / num_threads, 0 }, end = { width_ * (thread + 1) / num_threads, height_ };

    	for (double x = start.x; x < end.x; ++x) {
    	    for (double y = start.y; y < end.y; ++y) {
				Vector px = {x - width_ / 2, y - height_ / 2, 0};

				double  //proj1 = sqrt(cam.dir_.y_*cam.dir_.y_ + cam.dir_.z_*cam.dir_.z_),
						proj2 = sqrt(cam.dir_.z_*cam.dir_.z_ + cam.dir_.x_*cam.dir_.x_);

				double  //cos1 = 0, sin1 = 0, 
						cos2 = 0, sin2 = 0;
				//if (proj1 != 0) {
				//	cos1 = cam.dir_.z_ / proj1,
				//	sin1 = cam.dir_.y_ / proj1;
				//	px = {px.x_, px.y_*cos1 - px.z_*sin1, px.y_*sin1 + px.z_*cos1};
				//}

				if (proj2 > 0) {
					cos2 = cam.dir_.z_ / proj2,
					sin2 = cam.dir_.x_ / proj2;
					px = {px.x_*cos2 + px.z_*sin2, px.y_, -px.x_*sin2 + px.z_*cos2};
				}

				Vector dir = (cam.dir_ * 1000 + px).norm();
    	        draw_pixel({x,y,0}, rt.color({cam.pos_, dir, 1}));
    	    }
    	}
	}

	show_fps();

	txEnd();
}

void Window::show_fps() {
	double fps = txGetFPS();

	if      (fps < 10) txSetColor(TX_RED   );
	else if (fps < 20) txSetColor(TX_YELLOW);
	else 			   txSetColor(TX_GREEN );

	char text[3] = "";
	_itoa_s((int) fps, text, 10);
	txTextOut(10, 10, text);
}

void Window::move(Raytracer& rt, const Camera& cam) {
	    if (txMouseButtons() == 1) {
        POINT mouse = txMousePos();

        Vector px = {(double) mouse.x - width_ / 2, (double) mouse.y - height_ / 2, 0};

		double  //proj1 = sqrt(cam.dir_.y_*cam.dir_.y_ + cam.dir_.z_*cam.dir_.z_),
				proj2 = sqrt(cam.dir_.z_*cam.dir_.z_ + cam.dir_.x_*cam.dir_.x_);

		double  //cos1 = 0, sin1 = 0, 
				cos2 = 0, sin2 = 0;
		//if (proj1 != 0) {
		//	cos1 = cam.dir_.z_ / proj1,
		//	sin1 = cam.dir_.y_ / proj1;
		//	px = {px.x_, px.y_*cos1 - px.z_*sin1, px.y_*sin1 + px.z_*cos1};
		//}

		if (proj2 > 0) {
			cos2 = cam.dir_.z_ / proj2,
			sin2 = cam.dir_.x_ / proj2;
			px = {px.x_*cos2 + px.z_*sin2, px.y_, -px.x_*sin2 + px.z_*cos2};
		}

		Ray ray = { cam.pos_, (cam.dir_ * 1000 + px).norm() };

        int obj;
        Vector hit = rt.trace(ray, &obj);

        if (hit == NULLVEC) {
            return;
        }
		Vector t;
		//txLine(rt.objects_[obj]->center_.x_, rt.objects_[obj]->center_.y_, rt.objects_[obj]->center_.x_ , rt.objects_[obj]->center_.y_);
		//txLine(rt.objects_[obj]->center_.x_, rt.objects_[obj]->center_.y_, rt.objects_[obj]->center_.x_, rt.objects_[obj]->center_.y_);
		//txLine(rt.objects_[obj]->center_.x_, rt.objects_[obj]->center_.y_, rt.objects_[obj]->center_.x_, rt.objects_[obj]->center_.y_);
        rt.objects_[obj]->center_ += cam.dir_;
    }

    return;
}