#include "Window.hpp"

#include <omp.h>

Window::Window(int width, int height, LONG bottom_size, LONG right_size) :
	width_       (width),
	height_      (height),
	interf_      ({bottom_size, right_size}),
	Video_memory_(nullptr),
	window_      (NULL),
	should_close_(false)
	
{
	_txWindowStyle |= WS_MINIMIZEBOX | WS_MINIMIZEBOX;
	txCreateWindow(width_ + interf_.right_size_, height_ + interf_.bottom_size_);

	Video_memory_ = txVideoMemory();
	window_       = txWindow();

	txSelectFont("Consolas", 20, false, FW_BOLD);

	_txWindowUpdateInterval = 60;
}

Window::~Window() {
	txDisableAutoPause();
}

void Window::draw_pixel(const POINT& px, const Vector& color, int frames) {
	RGBQUAD* pixel;
	for (int i = 0; i < UPSCALING; ++i) {
		for (int j = 0; j < UPSCALING; ++j) {
			pixel = &Video_memory_[(height_ + (int) interf_.bottom_size_ - 1 - (int)px.y - i) * (width_ + (int)interf_.right_size_) + (int)px.x + j];

			pixel->rgbRed   = BYTE (color.x_ * 255);
			pixel->rgbGreen = BYTE (color.y_ * 255);
			pixel->rgbBlue  = BYTE (color.z_ * 255);

			//pixel->rgbRed   = BYTE ((pixel->rgbRed   * frames + color.x_ * 255) / (frames + 1));
			//pixel->rgbGreen = BYTE ((pixel->rgbGreen * frames + color.y_ * 255) / (frames + 1)); //денойзер работает не правильно
			//pixel->rgbBlue  = BYTE ((pixel->rgbBlue  * frames + color.z_ * 255) / (frames + 1));
		}
	}
}

void Window::update(Raytracer& rt, const Camera& cam, int frames) {
	if (!IsWindow(txWindow())) {
		should_close_ = true;
		return;
	}

	interf_.update(*this, txMousePos());

	txBegin();

	omp_set_num_threads(THREADS);
	
	#pragma omp parallel num_threads(THREADS)
	{
		int thread = omp_get_thread_num();

		assert(UPSCALING > 0);
		POINT start = { width_ * thread / THREADS / UPSCALING, 0 }, end = { width_ * (thread + 1) / THREADS / UPSCALING, height_ / UPSCALING };

    	for (int x = start.x; x < end.x; ++x) {
    	    for (int y = start.y; y < end.y; ++y) {
				POINT p = { x * UPSCALING, y * UPSCALING };

				Vector px = { (double) p.x - width_ / 2, (double) p.y - height_ / 2, 0};

				//px.rot(cam.angle_);

				Ray ray = { cam.pos_, ((Vector {0,0,1} * 1000 + px).norm()).rot(cam.angle_) };

    	        draw_pixel(p, rt.color(ray), frames);
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
	POINT mouse = txMousePos();

	if (interf_.fields_[1].visible_ &&
		txMouseButtons() == 1 && 
		mouse.x >= 0 && 
		mouse.x <= width_ &&
		mouse.y >= 0 &&
		mouse.y <= height_) {

        Vector px = {(double) mouse.x - width_ / 2, (double) mouse.y - height_ / 2, 0};

		double  proj2 = sqrt(cam.dir_.z_*cam.dir_.z_ + cam.dir_.x_*cam.dir_.x_);
		double  cos2 = 0, sin2 = 0;

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
		
		for (int button = 0; button < 12; ++button) {
			interf_.fields_[1].buttons_[button]->obj_ = rt.objects_[obj];
			interf_.fields_[1].buttons_[button]->text_ = std::to_string((int) *getParam(button, rt.objects_[obj]));

			interf_.fields_[1].buttons_[button]->draw();
		}

		return false;
        //rt.objects_[obj]->center_ += cam.dir_;

		//return true;
	}

    return false;
}

HPEN   setColor (COLORREF color, double thickness) {return txSetColor(color, thickness);}
HBRUSH setFillColor (COLORREF color) {return txSetFillColor(color);}
bool   rectangle (double x0, double y0, double x1, double y1) {return txRectangle(x0, y0, x1, y1);}
bool   drawText (double x0, double y0, double x1, double y1, const char text[], unsigned format) {return txDrawText(x0, y0, x1, y1, text, format);}
bool   bitBlt   (HDC destImage, double xDest, double yDest, double width, double height) {return txBitBlt(destImage, xDest, yDest, width, height, txDC());}
bool   isIconic () {return IsIconic(txWindow());}
POINT  mousePos () {return txMousePos();}