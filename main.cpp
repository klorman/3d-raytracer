#include "TXLib.h"
#include "Window.hpp"
#include "Raytracer.hpp"
#include "Camera.hpp"

#include <clocale>

#define LEN(arr) sizeof(arr) / sizeof(arr[0])

void start(Window& wnd);

void start(Window& wnd) {
    Object* objects[] = {
        new Sphere{{ 300, 400, 60 }, { 1, 1, 1 },     50,     {0.9, 1.5, 0.0, 0.0  }},
        new Sphere{{ 560, 400, 80 }, { 1, 1, 1 },     50,     {0.9, 5  , 0.0, 1.0  }},
        new Sphere{{ 600, 385, 10 }, { 1, 0, 0 },     30,     {0.9, 5  , 0.0, 1.0}},
        new Plane {{ 0  , 450, 0  }, { 1, 1, 0 }, { 0,-1, 0}, {0.9, 5  , 0.0, 0.1}},
        new Light {{ 300, 200,-200}, {0.9,0.9,0.9 },     200  ,          1            }
    };

    Raytracer rt = {LEN(objects), objects};

    Camera cam = {100, {600 ,385, -100}, {0, 0, 1}};
    
    bool is_moved = false;
    int  frames = 0;

    wnd.interf_.draw(wnd);

    while (!GetAsyncKeyState(VK_ESCAPE)) {  

        is_moved |= cam.move();
        is_moved |= wnd.move(rt, cam);

        is_moved ? frames = 0, is_moved = false : ++frames;

        wnd.update(rt, cam, frames);
    }
}

int main() {
    Interface interf(50, 300);

    Window wnd(800, 600, interf);

    AbstractButton* buttons[] = {
        new BasicButton{{wnd.width_,                                     0 }, {LONG (interf.right_size_ / 2)    , 30}, EVEC * 70, EVEC * 255, "Edit"},
        new BasicButton{{wnd.width_ + LONG (interf.right_size_ / 2) - 1, 0 }, {LONG (interf.right_size_ / 2 + 1), 30}, EVEC * 70, EVEC * 255, "Objects"},
        new BasicButton{{wnd.width_,                                     30}, {interf.right_size_               , 30}, EVEC * 70, EVEC * 255, "Create"}
    };

    wnd.interf_.button_count_ = LEN(buttons);
    wnd.interf_.buttons_      = buttons;

    
    
    start(wnd);
    
}