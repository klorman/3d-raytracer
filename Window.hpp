#pragma once
#include "Raytracer.hpp"
#include "Camera.hpp"
//#include "Interface.hpp"

#include "Button.hpp"

class Window;

class Interface {
public:
	const Vector BACKGROUND = { 70, 70, 70 };

    LONG bottom_size_, right_size_;
    int button_count_;
    AbstractButton** buttons_; 

    Interface(double bottom, double right);

    bool mouse_on_interface(const Window& wnd, const POINT& mouse_pos);
	void draw              (const Window& wnd);
    void update            (const Window& wnd, const POINT& mouse_pos);
};


class Window {
public:
	const int   UPSCALING = 2, 
				THREADS = 16; //количество используемых потоков

	int width_, height_;
	Interface interf_;
	RGBQUAD* Video_memory_;
	HDC dc_;


	Window(int width, int height, const Interface& interf);
	~Window();

	void draw_pixel(const POINT& px, const Vector& color, int frames);
	void update(Raytracer& rt, const Camera& cam, int frames);
	void show_fps();
	bool move(Raytracer& rt, const Camera& cam);

	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
};

Vector get_color(Raytracer& rt, Ray& ray);

