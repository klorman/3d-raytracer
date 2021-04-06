#include "TXLib.h"
#include "Window.hpp"
#include <iostream>
#include "Raytracer.hpp"
#include "Camera.hpp"

int main() {
    Window wnd(800, 600);

    Sphere sphere[] = {
        {{500,200,60},{0,0,255},50, {{1,1,1}, {1,1,1}, {1,1,1}}},
        {{560,400,80},{0,255,255},50, {{1,1,1}, {1,1,1}, {1,1,1}}},
        {{600,385,10},{255,0,0},30, {{1,1,1}, {1,1,1}, {1,1,1}}}
        
    };
    Light light[] = {{{600, 300, -2000}, 1}};

    Raytracer rt = {3, sphere, 1, light};

    Camera cam = {{500,300,-200}, {0,0,1}};

    
    while (!GetAsyncKeyState(VK_ESCAPE)) {  
        cam.move();      
        wnd.update(rt, cam);
    }
}


