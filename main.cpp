#include "TXLib.h"
#include "Window.hpp"
#include <iostream>

int main() {
    Window wnd(800, 600);
    txCreateWindow(wnd.width_, wnd.height_);
    wnd.Video_memory_ = txVideoMemory();

    
}