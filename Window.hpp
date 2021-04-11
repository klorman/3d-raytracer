#pragma once
#include "TXLib.h"
#include "Raytracer.hpp"
#include "Camera.hpp"

class Window {
public:
	const int UPSCALING = 2;

	int width_, height_;
	RGBQUAD* Video_memory_;

	Window(int width, int height);
	~Window();

	void draw_pixel(const Vector& coords, const Vector& color, int frames);
	void update(Raytracer& rt, const Camera& cam, int frames);
	void show_fps();
	bool move(Raytracer& rt, const Camera& cam);

	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
};

