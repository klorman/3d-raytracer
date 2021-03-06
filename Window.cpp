#include "Window.hpp"

#include <omp.h>

Window::Window(int width, int height, LONG bottom_size, LONG right_size, int canvas_width, int canvas_height) :
	width_               (width),
	height_              (height),
	Video_memory_        (nullptr),
	interf_              ({bottom_size, right_size}),
	window_              (NULL),
	should_close_        (false),
	canvas_width_        (canvas_width),
	canvas_height_       (canvas_height),
	canvas_video_memory_ (nullptr),
	canvas_              (txCreateCompatibleDC(canvas_width_, canvas_height_, NULL, &canvas_video_memory_)),
	distToScreen         (0)
{
	_txWindowStyle |= WS_MINIMIZEBOX;
	txCreateWindow(width_ + interf_.right_size_, height_ + interf_.bottom_size_);

	//::DWORD styles = ::GetWindowLongA(txWindow(), GWL_STYLE);
	//styles &= ~(WS_SYSMENU);
	//styles = ::SetWindowLongA(txWindow(), GWL_STYLE, styles);

	txTextCursor(false);

	Video_memory_ = txVideoMemory();
	window_       = txWindow();

	txSelectFont("Consolas", 20, false, FW_BOLD);
}

Window::~Window() {
	txDeleteDC(canvas_);
	txDisableAutoPause();
}

void Window::draw_pixel(const POINT& px, Vector color, int frames) {
	static std::vector<Vector> prev(canvas_width_ * canvas_height_);

	const double gamma = 2.2,
		         exposure = 1;

	color = Vector(1) - exp(-color * exposure);
	color = pow(color, 1 / gamma);

	for (int i = 0; i < prop.UPSCALING; ++i) {
		for (int j = 0; j < prop.UPSCALING; ++j) {
			RGBQUAD* pixel = &canvas_video_memory_[(canvas_height_ - 1 - px.y - i) * (canvas_width_) + px.x + j];

			int ind = (canvas_height_ - 1 - px.y) * (canvas_width_) + px.x;

			prev[ind].x_ = (prev[ind].x_ * frames + color.x_ * 255) / (frames + 1);
			prev[ind].y_ = (prev[ind].y_ * frames + color.y_ * 255) / (frames + 1);
			prev[ind].z_ = (prev[ind].z_ * frames + color.z_ * 255) / (frames + 1);

			pixel->rgbRed   = (BYTE) ROUND(prev[ind].x_);
			pixel->rgbGreen = (BYTE) ROUND(prev[ind].y_);
			pixel->rgbBlue  = (BYTE) ROUND(prev[ind].z_);
		}
	}
}

void Window::update(Raytracer& rt, const Camera& cam, int frames) {
	interf_.update(*this, txMousePos());

	Vector hit = rt.trace({cam.pos_, Vector {0, 0, 1}.rot(cam.angle_)}).first;
	prop.FOCUS = ((hit == NULLVEC) ? INF : hit - cam.pos_).length(); //??????????????????

	txBegin();

	omp_set_num_threads(THREADS);
	
	#pragma omp parallel num_threads(THREADS)
	{
		int thread = omp_get_thread_num();

		assert(prop.UPSCALING > 0);
		POINT begin = { LONG (canvas_width_ * thread / THREADS / prop.UPSCALING), 0 }, end = { LONG (canvas_width_ * (thread + 1) / THREADS / prop.UPSCALING), LONG (canvas_height_ / prop.UPSCALING) };

    	for (int x = begin.x; x < end.x; ++x) {
    	    for (int y = begin.y; y < end.y; ++y) {
				POINT p = { LONG (x * prop.UPSCALING), LONG (y * prop.UPSCALING) };

				Vector px = { (double) p.x - canvas_width_ / 2, (double) p.y - canvas_height_ / 2, 0};
				Vector matr = random_on_box(1, (double) canvas_height_ / canvas_width_) * prop.BLURRADIUS / 100;

				Vector start = cam.pos_ + matr.rot(cam.angle_);

				//double focalSize = prop.FOCUS * canvas_width_ / distToScreen;

				Ray ray = { start, ((Vector {0,0,1} * prop.FOCUS + px * prop.FOCUS / distToScreen) - matr).norm().rot(cam.angle_) };

    	        draw_pixel(p, rt.color(ray), frames);
    	    }
    	}
	}

	StretchBlt(txDC(), 0, 0, width_, height_, canvas_, 0, 0, canvas_width_, canvas_height_, SRCCOPY);

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
	if (rt.objects_.empty()) return 0;

	POINT mouse = txMousePos();

	static bool pressed = false;

	if (mouse.x >= 0 && 
		mouse.x <= width_ &&
		mouse.y >= 0 &&
		mouse.y <= height_) {

		if (txMouseButtons() == 1) pressed = true;

		else if (pressed) {
			mouse.x = mouse.x * canvas_width_  / width_;
			mouse.y = mouse.y * canvas_height_ / height_;

	        Vector px = {(double) mouse.x - canvas_width_ / 2, (double) mouse.y - canvas_height_ / 2, 0};

			Ray ray = { cam.pos_, ((Vector {0,0,1} * distToScreen + px).norm()).rot(cam.angle_) };

	        int obj;
	        Vector hit = rt.trace(ray, &obj).first;

			pressed = false;

			if (rt.objects_[obj]->status_) {
				rt.objects_[obj]->status_ = false;

				return 1;
			}

			for (int i = 0; i < rt.object_count_; ++i) rt.objects_[i]->status_ = false;

	        if (hit == NULLVEC) {
	            return 1; //?????????? ?????????????????? ?? ????????????????
	        }

			bindButtonsToObject(rt.objects_[obj]);

			rt.objects_[obj]->status_ = true;

			return obj + 2; //???????????????????? id ?????????????? + 2
		}
	}

	return 0; //???????????? ???? ??????????????????
}

void Window::bindButtonsToObject(Object* obj) {
	for (int button = posX; button <= matRough; ++button) {
		TextButton* editTextButton = reinterpret_cast<TextButton*>(interf_.fields_[1].buttons_[button]);

		editTextButton->val_  = getParam(editTextButton->bind_, obj);
		editTextButton->text_ = std::to_string(int (*getParam(button, obj) * editTextButton->mult_));

		if (interf_.fields_[0].buttons_[0]->status_ == 3) editTextButton->draw(interf_.fields_[1].canvas_, false);
	}
}

HPEN   setColor (COLORREF color, double thickness, HDC dc) {if (dc == NULL) dc = txDC(); return txSetColor(color, thickness, dc);}
HBRUSH setFillColor (COLORREF color, HDC dc) {if (dc == NULL) dc = txDC(); return txSetFillColor(color, dc);}
bool   rectangle (double x0, double y0, double x1, double y1, HDC dc) {if (dc == NULL) dc = txDC(); return txRectangle(x0, y0, x1, y1, dc);}
bool   drawText (double x0, double y0, double x1, double y1, const char text[], unsigned format, HDC dc) {if (dc == NULL) dc = txDC(); return txDrawText(x0, y0, x1, y1, text, format, dc);}
bool   copyFromWnd (HDC destImage,   double xDest, double yDest, double width, double height, double xSource, double ySource) {return txBitBlt(destImage, xDest, yDest, width, height, txDC(), xSource, ySource);}
bool   copyToWnd   (HDC SourceImage, double xDest, double yDest, double width, double height, double xSource, double ySource) {return txBitBlt(txDC(), xDest, yDest, width, height,SourceImage, xSource, ySource);}
bool   isIconic () {return IsIconic(txWindow());}
bool   isForeground() {return GetForegroundWindow() == txWindow();}
POINT  mousePos () {return txMousePos();}
int    beginWnd () {return txBegin();}
int    endWnd   () {return txEnd();}
bool   isDestroyed () {return _txMain;}

void redrawWnd() {
	HWND wnd = txWindow();
	if (wnd) RedrawWindow (wnd, NULL, NULL, RDW_INVALIDATE | RDW_INTERNALPAINT | RDW_UPDATENOW);
}

HCURSOR cursor_ = LoadCursor(0, IDC_ARROW);
bool    closed = false;

void   drawCursor (HCURSOR cursor) {cursor_ = cursor; txSetWindowsHook(myProc);}
bool   isClosed   () {txSetWindowsHook(myProc); return closed;}

LRESULT CALLBACK myProc (HWND window, UINT message, WPARAM wParam, LPARAM lParam) {
	(void) window;
	(void) wParam;

	if (message == WM_NCLBUTTONDOWN && wParam == HTCLOSE) {
		closed = true;

		return true;
	}

	if (message == WM_SETCURSOR && LOWORD (lParam) == HTCLIENT) {
	    SetCursor (cursor_);
	
		return true;
	}

	return false;
}