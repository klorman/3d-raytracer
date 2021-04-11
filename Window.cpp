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

void Window::draw_pixel(const Vector& coords, const Vector& color, int frames) {
	RGBQUAD* pixel = &Video_memory_[(height_ - 1 - (int)coords.y_) * width_ + (int)coords.x_];

	pixel->rgbRed   = BYTE (color.x_ * 255);
	pixel->rgbGreen = BYTE (color.y_ * 255);
	pixel->rgbBlue  = BYTE (color.z_ * 255);

	//pixel->rgbRed   = BYTE ((pixel->rgbRed   * frames + color.x_ * 255) / (frames + 1));
	//pixel->rgbGreen = BYTE ((pixel->rgbGreen * frames + color.y_ * 255) / (frames + 1)); //денойзер работает не правильно
	//pixel->rgbBlue  = BYTE ((pixel->rgbBlue  * frames + color.z_ * 255) / (frames + 1));
}

void Window::update(Raytracer& rt, const Camera& cam, int frames) {
	txBegin();

	const int num_threads = 16; //количество используемых потоков
	omp_set_num_threads(num_threads);
	
	#pragma omp parallel num_threads(num_threads)
	{
		int thread = omp_get_thread_num();

		assert(UPSCALING > 0);
		POINT start = { width_ * thread / num_threads / UPSCALING, 0 }, end = { width_ * (thread + 1) / num_threads / UPSCALING, height_ / UPSCALING };

    	for (int x = start.x; x < end.x; ++x) {
    	    for (int y = start.y; y < end.y; ++y) {
				POINT p = { x * UPSCALING, y * UPSCALING };

				Vector px = { (double) p.x - width_ / 2, (double) p.y - height_ / 2, 0};

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

				Vector dir = (cam.dir_ * 1000 + px).norm(), color = rt.color({cam.pos_, dir, 1});

				for (double i = 0; i < UPSCALING; ++i) {
					for (double j = 0; j < UPSCALING; ++j) {
    	        		draw_pixel({ p.x + i, p.y + j, 0 }, color, frames);
					}
				}
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

	char text[4] = "";
	_itoa_s((int) fps, text, 10);
	txTextOut(10, 10, text);
}

bool Window::move(Raytracer& rt, const Camera& cam) {
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
            return false;
        }

        rt.objects_[obj]->center_ += cam.dir_;

		return true;
	}

    return false;
}