#include "TXLib.h"
#include "Window.hpp"
#include "Raytracer.hpp"
#include "Camera.hpp"

#define LEN(arr) sizeof(arr) / sizeof(arr[0])

void start(Window& wnd);

void start(Window& wnd) {
    Object* objects[] = {
        new Sphere{{ 300, 400, 60 }, { 1, 1, 1 },     50,     {0.0, 1.5, 0.9, 1.0  }},
        new Sphere{{ 560, 400, 80 }, { 1, 1, 1 },     50,     {1.0, 5  , 0.0, 1.0  }},
        new Sphere{{ 600, 385, 10 }, { 1, 0, 0 },     30,     {0.5, 5  , 0.0, 0.001}},
        new Plane {{ 0  , 450, 0  }, { 1, 1, 0 }, { 0,-1, 0}, {0.9, 5  , 0.0, 0.000}},
        new Light {{ 300, 250,-200}, { 1, 1, 1 },     50  ,          1            }
    };

    Raytracer rt = {LEN(objects), objects};

    Camera cam = {100, {600 ,385, -100}, {0, 0, 1}};
    
    bool is_moved = false;
    int  frames = 0;

    while (!GetAsyncKeyState(VK_ESCAPE)) {  

        is_moved |= cam.move();
        is_moved |= wnd.move(rt, cam);

        is_moved ? frames = 0, is_moved = false : ++frames;

        wnd.update(rt, cam, frames);
    }
}

int main() {

    Window wnd(800, 600);
    
    start(wnd);
    
}