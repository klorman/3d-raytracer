#include "TXLib.h"
#include "Window.hpp"
#include "Raytracer.hpp"
#include "Camera.hpp"
#include "Sphere.hpp"
#include "Plane.hpp"

#define LEN(arr) sizeof(arr) / sizeof(arr[0])

void start(Window& wnd) {
    Object* objects[] = {
        new Sphere{{500,200,60}, {0,  0,  255},    50,    {0.4, 1, 0.5}},
        new Sphere{{560,400,80}, {255,255,255},    50,    {0.9, 1, 0.5}},
        new Sphere{{600,385,10}, {255,0,  0  },    30,    {0.0, 1, 0.5}},
        new Plane {{0,  450,0 }, {255,255,0  }, {0,-1,0}, {0.0, 1, 0.5}}
    };

    Light light[] = {{{300, 0, -200}, 1}};

    Raytracer rt = {LEN(objects), objects, LEN(light), light};

    Camera cam = {10, {600 ,385, -300}, {0, 0, 1}};
    
    while (!GetAsyncKeyState(VK_ESCAPE)) {  
        cam.move();     
        rt.lights_[0].pos_ += {0,0,0}; 
        wnd.update(rt, cam);
    }
}

int main() {

    Window wnd(800, 600);
    
    start(wnd);
}