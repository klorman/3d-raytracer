#pragma once
#include "Raytracer.hpp"
#include "Camera.hpp"
#include "Field.hpp"

class Window;
class Camera;
class Field;

class Interface {
public:
    LONG               bottom_size_, right_size_;
    int                field_count_;
    std::vector<Field> fields_; 

    Interface(LONG bottom, LONG right);

	void addField(bool visible, POINT pos, POINT size);
    bool mouse_on_interface (const Window& wnd, const POINT& mouse_pos);
	void draw               ();
    void update             (Window& wnd, const POINT& mouse_pos);
};

class Window {
public:
	//double UPSCALING = 2;  //во сколько раз меньше изображение будет рендериться
	const int THREADS   = 16; //количество используемых потоков

	int         width_, height_;
	RGBQUAD*    Video_memory_;
	Interface   interf_;
	HWND        window_;
	bool        should_close_;
	int         canvas_width_, canvas_height_;
	RGBQUAD*    canvas_video_memory_;
	HDC         canvas_;

	double distToScreen;

	Window(int width, int height, LONG bottom_size_, LONG right_size_, int canvas_width = 150, int canvas_height = 100);
	~Window();

	void draw_pixel          (const POINT& px, Vector color, int frames);
	void update              (Raytracer& rt, const Camera& cam, int frames);
	void show_fps            ();
	int  selectObject        (Raytracer& rt, const Camera& cam);
	void bindButtonsToObject (Object* obj);

	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
};

HPEN   setColor       (COLORREF color, double thickness = 1, HDC dc = NULL);
HBRUSH setFillColor   (COLORREF color, HDC dc = NULL);
bool   rectangle      (double x0, double y0, double x1, double y1, HDC dc = NULL);
bool   drawText       (double x0, double y0, double x1, double y1, const char text[], unsigned format = DT_CENTER | DT_VCENTER | DT_WORDBREAK | DT_WORD_ELLIPSIS, HDC dc = NULL);
bool   copyFromWnd    (HDC destImage,   double xDest, double yDest, double width, double height, double xSource = 0, double ySource = 0);
bool   copyToWnd      (HDC SourceImage, double xDest, double yDest, double width, double height, double xSource = 0, double ySource = 0);
bool   isIconic       ();
bool   isForeground   ();
POINT  mousePos       ();
int    beginWnd       ();
int    endWnd         ();
bool   isDestroyed    ();

void   redrawWnd      ();
bool   isClosed       ();
void   drawCursor     (HCURSOR cursor);
LRESULT CALLBACK myProc (HWND window, UINT message, WPARAM wParam, LPARAM lParam);