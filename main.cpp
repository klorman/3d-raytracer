#include "TXLib.h"
#include "Window.hpp"
#include <iostream>
#include "Raytracer.hpp"

int main() {
    Window wnd(800, 600);

    Sphere sphere[] = {{{400,300,200},{255,0,0},150, {{1,1,1}, {1,1,1}, {1,1,1}}}};
    Light light[] = {{{100, 100, -100}, 1}};

    Raytracer rt = {1, sphere, 1, light};

    for (double x = 0; x < wnd.width_; ++x) {
        for (double y = 0; y < wnd.height_; ++y) {
            wnd.draw_pixel({x,y,0}, rt.color({{x,y,0}, {0, 0, 1}}));
        }
    }
}


