#pragma once
#include "TXLib.h"
#include "Raytracer.hpp"
#include "Camera.hpp"

class Window {
public:
	int width_, height_;
	RGBQUAD* Video_memory_;
	Window(int width, int height);
	~Window();

	void draw_pixel(const Vector& coords, const Vector& color);
	void update(Raytracer& rt, const Camera& cam);
};

