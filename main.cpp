#include "TXLib.h"
#include "Window.hpp"
#include <iostream>
#include "Raytracer.hpp"

int main() {
    Window wnd(800, 600);
    txCreateWindow(wnd.width_, wnd.height_);
    //txCreateWindow(800, 600);
    wnd.Video_memory_ = txVideoMemory();
    
    Sphere sphere[] = {{{400,300,100},{255,0,0},50, {{1,1,1}, {1,1,1}, {1,1,1}}}};
    Light light[] = {{{400, 300, 0}, 1}};

    Raytracer rt = {1, sphere, 1, light};

    for (double x = 0; x < wnd.width_; ++x) {
        for (double y = 0; y < wnd.height_; ++y) {
            //std::cout << x << y << std::endl;
            wnd.draw_pixel({x,y,0},{0,128,0});
            //wnd.draw_pixel({x,y,0}, rt.color({{x,y,0}, {0, 0, 1}}));
        }
    }
}