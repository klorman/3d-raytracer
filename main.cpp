#include "TXLib.h"
#include "Window.hpp"
#include "Raytracer.hpp"
#include "Camera.hpp"

#define LEN(arr) sizeof(arr) / sizeof(arr[0])

void Save();
void Load();
void Screenshot();
void Exit();

Window wnd(800, 600, 50, 300);

void start();

void start() {
    Object* objects[] = {
        new Sphere{{ 300, 400, 60 }, { 1.0, 1.0, 1.0 },     50,     { 0.9, 1.5, 0.0, 0.0  }},
        new Sphere{{ 560, 400, 80 }, { 1.0, 1.0, 1.0 },     50,     { 0.9, 5.0, 0.0, 1.0  }},
        new Sphere{{ 600, 385, 10 }, { 1.0, 0.0, 0.0 },     30,     { 0.9, 5.0, 0.0, 1.0  }},
        new Plane {{ 0  , 450, 0  }, { 1.0, 1.0, 0.0 }, { 0,-1, 0}, { 0.9, 5.0, 0.0, 0.1  }},
        new Light {{ 300, 200,-200}, { 0.9, 0.9, 0.9 },     200  ,            1            }
    };

    Raytracer rt = {LEN(objects), objects};

    Camera cam = {100, {600 ,385, -100}, {0, 0, 1}};
    
    bool is_moved = false;
    int  frames = 0;

    wnd.interf_.draw(wnd);

    while (!wnd.should_close_) { 
        if (!IsWindowVisible(wnd.getWindow())) continue;
        
        is_moved |= cam.move();
        is_moved |= wnd.move(rt, cam);

        is_moved ? frames = 0, is_moved = false : ++frames;

        wnd.update(rt, cam, frames);
    }
}

int main() {
    AbstractButton* buttons[] = {
        new BasicButton{{wnd.width_                                         , 0           }, {LONG (wnd.interf_.right_size_ / 3), 30}, EVEC * 70, EVEC * 255, "Edit"},
        new BasicButton{{wnd.width_ + LONG (wnd.interf_.right_size_ / 3)    , 0           }, {LONG (wnd.interf_.right_size_ / 3), 30}, EVEC * 70, EVEC * 255, "Objects"},
        new BasicButton{{wnd.width_ + LONG (wnd.interf_.right_size_ / 3) * 2, 0           }, {LONG (wnd.interf_.right_size_ / 3), 30}, EVEC * 70, EVEC * 255, "Settings"},
        new BasicButton{{wnd.width_                                         , 30          }, {      wnd.interf_.right_size_     , 30}, EVEC * 70, EVEC * 255, "Create"},
        new BasicButton{{wnd.width_                                         , wnd.height_ }, {LONG (wnd.interf_.right_size_ / 4), 50}, EVEC * 70, EVEC * 255, "Save"},
        new BasicButton{{wnd.width_ + LONG (wnd.interf_.right_size_ / 4)    , wnd.height_ }, {LONG (wnd.interf_.right_size_ / 4), 50}, EVEC * 70, EVEC * 255, "Load"},
        new BasicButton{{wnd.width_ + LONG (wnd.interf_.right_size_ / 4) * 2, wnd.height_ }, {LONG (wnd.interf_.right_size_ / 4), 50}, EVEC * 70, EVEC * 255, "Screenshot"},
        new BasicButton{{wnd.width_ + LONG (wnd.interf_.right_size_ / 4) * 3, wnd.height_ }, {LONG (wnd.interf_.right_size_ / 4), 50}, EVEC * 70, EVEC * 255, "Exit", Exit}
    };

    wnd.interf_.button_count_ = LEN(buttons);
    wnd.interf_.buttons_      = buttons;

    start();
    
}

void Exit() {
    wnd.should_close_ = true;
}