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

    Interface(LONG bottom, LONG right);

    bool mouse_on_interface(const Window& wnd, const POINT& mouse_pos);
	void draw              (Window& wnd);
    void update            (Window& wnd, const POINT& mouse_pos);
};

class Window {
public:
	const double UPSCALING = 2;  //во сколько раз меньше изображение будет рендериться
	const int    THREADS   = 16; //количество используемых потоков

	int width_, height_;
	Interface interf_;
	RGBQUAD* Video_memory_;

	bool should_close_;


	Window(int width, int height, LONG bottom_size_, LONG right_size_);
	~Window();

	void draw_pixel(const POINT& px, const Vector& color, int frames);
	void update(Raytracer& rt, const Camera& cam, int frames);
	void show_fps();
	bool move(Raytracer& rt, const Camera& cam);
	HDC& get_DC() const;
	HWND getWindow() const;

	void Save();
	void Load();
	void Screenshot();
	void Exit();

	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
};

Vector get_color(Raytracer& rt, Ray& ray);

