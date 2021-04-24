#include "Window.hpp"

#include <omp.h>

Window::Window(int width, int height, LONG bottom_size, LONG right_size, Properties* prop) :
	width_        (width),
	height_       (height),
	interf_       ({bottom_size, right_size}),
	Video_memory_ (nullptr),
	window_       (NULL),
	should_close_ (false),
	prop_         (prop)
	
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
	for (int i = 0; i < prop_->UPSCALING; ++i) {
		for (int j = 0; j < prop_->UPSCALING; ++j) {
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
	interf_.update(*this, txMousePos());

	txBegin();

	omp_set_num_threads(THREADS);
	
	#pragma omp parallel num_threads(THREADS)
	{
		int thread = omp_get_thread_num();

		assert(prop_->UPSCALING > 0);
		POINT start = { LONG (width_ * thread / THREADS / prop_->UPSCALING), 0 }, end = { LONG (width_ * (thread + 1) / THREADS / prop_->UPSCALING), LONG (height_ / prop_->UPSCALING) };

    	for (int x = start.x; x < end.x; ++x) {
    	    for (int y = start.y; y < end.y; ++y) {
				POINT p = { LONG (x * prop_->UPSCALING), LONG (y * prop_->UPSCALING) };

				Vector px = { (double) p.x - width_ / 2, (double) p.y - height_ / 2, 0};

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

int Window::selectObject(Raytracer& rt, const Camera& cam) {
	POINT mouse = txMousePos();

	if (txMouseButtons() == 1 && 
		mouse.x >= 0 && 
		mouse.x <= width_ &&
		mouse.y >= 0 &&
		mouse.y <= height_) {

        Vector px = {(double) mouse.x - width_ / 2, (double) mouse.y - height_ / 2, 0};

		Ray ray = { cam.pos_, ((Vector {0,0,1} * 1000 + px).norm()).rot(cam.angle_) };

        int obj;
        Vector hit = rt.trace(ray, &obj);

        if (hit == NULLVEC) {
            return 1; //снято выделение с объектов
        }
		
		for (int button = posX; button <= colZ; ++button) {
			TextButton* editTextButton = reinterpret_cast<TextButton*>(interf_.fields_[1].buttons_[button]);

			editTextButton->val_  = getParam(editTextButton->bind_, rt.objects_[obj]);
			editTextButton->text_ = std::to_string((int) *getParam(button, rt.objects_[obj]) * editTextButton->mult_);

			if (interf_.fields_[0].buttons_[0]->status_ == 3) editTextButton->draw();
		}

		return obj + 2; //возвращаем id объекта + 2
	}

	return 0; //ничего не произошло
}

HPEN   setColor (COLORREF color, double thickness) {return txSetColor(color, thickness);}
HBRUSH setFillColor (COLORREF color) {return txSetFillColor(color);}
bool   rectangle (double x0, double y0, double x1, double y1) {return txRectangle(x0, y0, x1, y1);}
bool   drawText (double x0, double y0, double x1, double y1, const char text[], unsigned format) {return txDrawText(x0, y0, x1, y1, text, format);}
bool   bitBlt   (HDC destImage, double xDest, double yDest, double width, double height) {return txBitBlt(destImage, xDest, yDest, width, height, txDC());}
bool   isIconic () {return IsIconic(txWindow());}
bool   isForeground() {return GetForegroundWindow() == txWindow();}
POINT  mousePos () {return txMousePos();}

LPCSTR cursorName_ = IDC_ARROW;

void   hideCursor () {txSetWindowsHook(hideCursorProc);}
void   drawCursor (LPCSTR cursorName) {cursorName_ = cursorName; txSetWindowsHook(drawCursorProc);}

LRESULT CALLBACK hideCursorProc (HWND window, UINT message, WPARAM wParam, LPARAM lParam) {
	(void) window;
	(void) wParam;

    if (message == WM_SETCURSOR && LOWORD (lParam) == HTCLIENT) {
        SetCursor (NULL);
        return true;     
    }

    return false;
}

LRESULT CALLBACK drawCursorProc (HWND window, UINT message, WPARAM wParam, LPARAM lParam) {
	(void) window;
	(void) wParam;

	if (message == WM_SETCURSOR && LOWORD (lParam) == HTCLIENT) {
	    SetCursor (LoadCursor(0, cursorName_));
	
		return true;
	}

    return false;
}