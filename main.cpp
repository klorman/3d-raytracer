#include "TXLib.h"
#include "Window.hpp"
#include "Raytracer.hpp"
#include "Camera.hpp"

#define LEN(arr) sizeof(arr) / sizeof(arr[0])

void start(Window& wnd);

void start(Window& wnd) {
    Object* objects[] = {
        new Sphere{{ 300, 400, 60 }, { 1, 1, 1 },     50,     {0.0, 1.5, 1.0, 1.0  }},
        new Sphere{{ 560, 400, 80 }, { 1, 1, 1 },     50,     {1.0, 5  , 0.0, 1.0  }},
        new Sphere{{ 600, 385, 10 }, { 1, 0, 0 },     30,     {0.5, 5  , 0.0, 0.001}},
        new Plane {{ 0  , 450, 0  }, { 1, 1, 0 }, { 0,-1, 0}, {0.2, 5  , 0.0, 0.005}},
        new Light {{ 300, 0  ,-200}, { 1, 1, 1 },    100  ,            1            }
    };

    Light light[] = {{{300,  0, -200}, {1,1,1}, 100, 1}};

    Raytracer rt = {LEN(objects), objects, LEN(light), light};

    Camera cam = {100, {600 ,385, -100}, {0, 0, 1}};
    
    while (!GetAsyncKeyState(VK_ESCAPE)) {  
        cam.move();     
        //rt.lights_[0].center_ += {0,0,0}; 
        wnd.move(rt, cam);
        wnd.update(rt, cam);
    }
}

int main() {

    Window wnd(800, 600);
    
    start(wnd);
    
}