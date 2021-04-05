#pragma once
#include "TXLib.h"
#include "Vector.hpp"

class Window {
public:
	int width_, height_;
	RGBQUAD* Video_memory_;
	Window(int width, int height);

	void draw_pixel(Vector coords, Vector color);

};

