#pragma once
#include "Raytracer.hpp"
#include "Camera.hpp"
#include "Field.hpp"

class Window;
class Camera;
class Field;

class Interface {
public:
	const Vector BACKGROUND = { 70, 70, 70 };

    LONG               bottom_size_, right_size_;
    int                field_count_;
    std::vector<Field> fields_; 

    Interface(LONG bottom, LONG right);

	void addField(bool visible, POINT pos, POINT size);
    bool mouse_on_interface (const Window& wnd, const POINT& mouse_pos);
	void draw               (Window& wnd);
    void update             (Window& wnd, const POINT& mouse_pos);
};

class Window {
public:
	//double UPSCALING = 2;  //во сколько раз меньше изображение будет рендериться
	const int THREADS   = 16; //количество используемых потоков

	int         width_, height_;
	Interface   interf_;
	RGBQUAD*    Video_memory_;
	HWND        window_;
	bool        should_close_;
	Properties* prop_;

	Window(int width, int height, LONG bottom_size_, LONG right_size_, Properties* prop);
	~Window();

	void draw_pixel          (const POINT& px, const Vector& color, int frames);
	void update              (Raytracer& rt, const Camera& cam, int frames);
	void show_fps            ();
	int  selectObject        (Raytracer& rt, const Camera& cam);
	void bindButtonsToObject (Object* obj);

	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
};

HPEN   setColor       (COLORREF color, double thickness = 1);
HBRUSH setFillColor   (COLORREF color);
bool   rectangle      (double x0, double y0, double x1, double y1);
bool   drawText       (double x0, double y0, double x1, double y1, const char text[], unsigned format = DT_CENTER | DT_VCENTER | DT_WORDBREAK | DT_WORD_ELLIPSIS);
bool   bitBlt         (HDC destImage, double xDest, double yDest, double width, double height);
bool   isIconic       ();
bool   isForeground   ();
POINT  mousePos       ();

void   hideCursor     ();
void   drawCursor     (LPCSTR cursorName); //их можно объединить
LRESULT CALLBACK hideCursorProc (HWND window, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK drawCursorProc (HWND window, UINT message, WPARAM wParam, LPARAM lParam);