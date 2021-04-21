#include "TXLib.h"
#include "Window.hpp"
#include "Raytracer.hpp"
#include "Camera.hpp"

#include <ctime>

#define LEN(arr) sizeof(arr) / sizeof(arr[0])

std::string getTime();

void Edit();
void Objects();
void Settings();

void Save();
void Load();
void Screenshot();
void Exit();

Window wnd(800, 600, 50, 300);

void start();
void createFields();

void start() {
    Object* objects[] = {
        new Sphere{{ 0.0, 1.5, 0.9, 1.0  },     50      , { 300, 400, 60 }, { 1.0, 1.0, 1.0 }            }, //прозрачный
        new Sphere{{ 0.9, 1.0, 0.0, 1.0  },     50      , { 560, 400, 80 }, { 1.0, 1.0, 1.0 }            }, //гладкий
        new Sphere{{ 0.9, 1.0, 0.0, 1.0  }, {30, 30, 60}, { 600, 385, 10 }, { 1.0, 0.0, 0.0 }            }, //гладкий
        new Sphere{{ 0.9, 1.0, 0.0, 0.0  },     50      , { 400, 400, 100}, { 1.0, 1.0, 1.0 }            }, //матовый
        new Box   {{ 0.9, 1.0, 0.0, 1.0  }, {50, 20, 50}, {   0, 400, 200}, { 0.3, 0.3, 1.0 }, (Vector { 1, 1, 1}).norm()}, //гладкий
        new Plane {{ 0.9, 1.0, 0.0, 0.1  }              , { 0  , 450, 0  }, { 1.0, 1.0, 0.0 }, { 0,-1, 0}},
        new Sphere{{ 0.0, 1.0,-1.0, 0.0  },     200     , { 300, 200,-200}, { 0.9, 0.9, 0.9 }            }  //источник
    };

    Raytracer rt = {LEN(objects), objects};

    Camera cam = {100, {600 ,385, -100}, {0, 0, 1}, {0, 0, 0}};
    
    bool is_moved = false;
    int  frames = 0;

    wnd.interf_.draw(wnd);

    while (!wnd.should_close_) { 
        if (!isForeground()) continue;

        is_moved |= cam.move();
        is_moved |= wnd.move(rt, cam);

        is_moved ? frames = 0, is_moved = false : ++frames;

        wnd.update(rt, cam, frames);
    }
}

void createFields() {
    AbstractButton* menuButtons[] = {
        new BasicButton{{wnd.width_                                         , 0           }, {LONG (wnd.interf_.right_size_ / 3), 30}, EVEC * 70, EVEC * 255, "Edit"},
        new BasicButton{{wnd.width_ + LONG (wnd.interf_.right_size_ / 3)    , 0           }, {LONG (wnd.interf_.right_size_ / 3), 30}, EVEC * 70, EVEC * 255, "Objects"},
        new BasicButton{{wnd.width_ + LONG (wnd.interf_.right_size_ / 3) * 2, 0           }, {LONG (wnd.interf_.right_size_ / 3), 30}, EVEC * 70, EVEC * 255, "Settings"},
        new BasicButton{{wnd.width_                                         , wnd.height_ }, {LONG (wnd.interf_.right_size_ / 4), 50}, EVEC * 70, EVEC * 255, "Save"},
        new BasicButton{{wnd.width_ + LONG (wnd.interf_.right_size_ / 4)    , wnd.height_ }, {LONG (wnd.interf_.right_size_ / 4), 50}, EVEC * 70, EVEC * 255, "Load"},
        new BasicButton{{wnd.width_ + LONG (wnd.interf_.right_size_ / 4) * 2, wnd.height_ }, {LONG (wnd.interf_.right_size_ / 4), 50}, EVEC * 70, EVEC * 255, "Screenshot", Screenshot},
        new BasicButton{{wnd.width_ + LONG (wnd.interf_.right_size_ / 4) * 3, wnd.height_ }, {LONG (wnd.interf_.right_size_ / 4), 50}, EVEC * 70, EVEC * 255, "Exit", Exit}        
    };
    AbstractButton* editButtons[] = {
        new TextButton {posX, {wnd.width_ + LONG (wnd.interf_.right_size_ / 3), 70 }, {LONG (wnd.interf_.right_size_ / 3), 30}, EVEC * 90, EVEC * 255},
        new TextButton {posY, {wnd.width_ + LONG (wnd.interf_.right_size_ / 3), 100}, {LONG (wnd.interf_.right_size_ / 3), 30}, EVEC * 90, EVEC * 255},
        new TextButton {posZ, {wnd.width_ + LONG (wnd.interf_.right_size_ / 3), 130}, {LONG (wnd.interf_.right_size_ / 3), 30}, EVEC * 90, EVEC * 255},
        new TextButton {rotX, {wnd.width_ + LONG (wnd.interf_.right_size_ / 3), 170}, {LONG (wnd.interf_.right_size_ / 3), 30}, EVEC * 90, EVEC * 255},
        new TextButton {rotY, {wnd.width_ + LONG (wnd.interf_.right_size_ / 3), 200}, {LONG (wnd.interf_.right_size_ / 3), 30}, EVEC * 90, EVEC * 255},
        new TextButton {rotZ, {wnd.width_ + LONG (wnd.interf_.right_size_ / 3), 230}, {LONG (wnd.interf_.right_size_ / 3), 30}, EVEC * 90, EVEC * 255},
        new TextButton {szX , {wnd.width_ + LONG (wnd.interf_.right_size_ / 3), 270}, {LONG (wnd.interf_.right_size_ / 3), 30}, EVEC * 90, EVEC * 255},
        new TextButton {szY , {wnd.width_ + LONG (wnd.interf_.right_size_ / 3), 300}, {LONG (wnd.interf_.right_size_ / 3), 30}, EVEC * 90, EVEC * 255},
        new TextButton {szZ , {wnd.width_ + LONG (wnd.interf_.right_size_ / 3), 330}, {LONG (wnd.interf_.right_size_ / 3), 30}, EVEC * 90, EVEC * 255},
        new TextButton {colX, {wnd.width_ + LONG (wnd.interf_.right_size_ / 3), 370}, {LONG (wnd.interf_.right_size_ / 3), 30}, EVEC * 90, EVEC * 255},
        new TextButton {colY, {wnd.width_ + LONG (wnd.interf_.right_size_ / 3), 400}, {LONG (wnd.interf_.right_size_ / 3), 30}, EVEC * 90, EVEC * 255},
        new TextButton {colZ, {wnd.width_ + LONG (wnd.interf_.right_size_ / 3), 430}, {LONG (wnd.interf_.right_size_ / 3), 30}, EVEC * 90, EVEC * 255},

        new BasicButton{{wnd.width_, 30              }, {wnd.interf_.right_size_, 30}, EVEC * 70, EVEC * 255, "Create"},
        new BasicButton{{wnd.width_, wnd.height_ - 30}, {wnd.interf_.right_size_, 30}, EVEC * 70, EVEC * 255, "Delete"},
    };
    Textbox editTextBoxes[] = {
        {{wnd.width_, 100}, {LONG (wnd.interf_.right_size_ / 3), 30}, "Сoordinates:"}
    };

    Field fields[] = {
        {0, LEN(menuButtons), 0,                  menuButtons, nullptr},
        {0, LEN(editButtons), LEN(editTextBoxes), editButtons, editTextBoxes}
    };

    wnd.interf_.field_count_ = LEN(fields);
    wnd.interf_.fields_ = fields;
}

int main() {
    //createFields();

    AbstractButton* menuButtons[] = {
        new BasicButton{{wnd.width_                                         , 0           }, {LONG (wnd.interf_.right_size_ / 3), 30}, EVEC * 70, EVEC * 255, "Edit",       Edit},
        new BasicButton{{wnd.width_ + LONG (wnd.interf_.right_size_ / 3)    , 0           }, {LONG (wnd.interf_.right_size_ / 3), 30}, EVEC * 70, EVEC * 255, "Objects",    Objects},
        new BasicButton{{wnd.width_ + LONG (wnd.interf_.right_size_ / 3) * 2, 0           }, {LONG (wnd.interf_.right_size_ / 3), 30}, EVEC * 70, EVEC * 255, "Settings",   Settings},
        new BasicButton{{wnd.width_                                         , wnd.height_ }, {LONG (wnd.interf_.right_size_ / 4), 50}, EVEC * 70, EVEC * 255, "Save",       Save},
        new BasicButton{{wnd.width_ + LONG (wnd.interf_.right_size_ / 4)    , wnd.height_ }, {LONG (wnd.interf_.right_size_ / 4), 50}, EVEC * 70, EVEC * 255, "Load",       Load},
        new BasicButton{{wnd.width_ + LONG (wnd.interf_.right_size_ / 4) * 2, wnd.height_ }, {LONG (wnd.interf_.right_size_ / 4), 50}, EVEC * 70, EVEC * 255, "Screenshot", Screenshot},
        new BasicButton{{wnd.width_ + LONG (wnd.interf_.right_size_ / 4) * 3, wnd.height_ }, {LONG (wnd.interf_.right_size_ / 4), 50}, EVEC * 70, EVEC * 255, "Exit",       Exit}        
    };
    AbstractButton* editButtons[] = {
        new TextButton {posX, {wnd.width_ + LONG (wnd.interf_.right_size_ / 3), 90 }, {LONG (wnd.interf_.right_size_ / 3), 30}, EVEC * 90, EVEC * 255},
        new TextButton {posY, {wnd.width_ + LONG (wnd.interf_.right_size_ / 3), 120}, {LONG (wnd.interf_.right_size_ / 3), 30}, EVEC * 90, EVEC * 255},
        new TextButton {posZ, {wnd.width_ + LONG (wnd.interf_.right_size_ / 3), 150}, {LONG (wnd.interf_.right_size_ / 3), 30}, EVEC * 90, EVEC * 255},
        new TextButton {rotX, {wnd.width_ + LONG (wnd.interf_.right_size_ / 3), 210}, {LONG (wnd.interf_.right_size_ / 3), 30}, EVEC * 90, EVEC * 255},
        new TextButton {rotY, {wnd.width_ + LONG (wnd.interf_.right_size_ / 3), 240}, {LONG (wnd.interf_.right_size_ / 3), 30}, EVEC * 90, EVEC * 255},
        new TextButton {rotZ, {wnd.width_ + LONG (wnd.interf_.right_size_ / 3), 270}, {LONG (wnd.interf_.right_size_ / 3), 30}, EVEC * 90, EVEC * 255},
        new TextButton {szX , {wnd.width_ + LONG (wnd.interf_.right_size_ / 3), 330}, {LONG (wnd.interf_.right_size_ / 3), 30}, EVEC * 90, EVEC * 255},
        new TextButton {szY , {wnd.width_ + LONG (wnd.interf_.right_size_ / 3), 360}, {LONG (wnd.interf_.right_size_ / 3), 30}, EVEC * 90, EVEC * 255},
        new TextButton {szZ , {wnd.width_ + LONG (wnd.interf_.right_size_ / 3), 390}, {LONG (wnd.interf_.right_size_ / 3), 30}, EVEC * 90, EVEC * 255},
        new TextButton {colX, {wnd.width_ + LONG (wnd.interf_.right_size_ / 3), 450}, {LONG (wnd.interf_.right_size_ / 3), 30}, EVEC * 90, EVEC * 255},
        new TextButton {colY, {wnd.width_ + LONG (wnd.interf_.right_size_ / 3), 480}, {LONG (wnd.interf_.right_size_ / 3), 30}, EVEC * 90, EVEC * 255},
        new TextButton {colZ, {wnd.width_ + LONG (wnd.interf_.right_size_ / 3), 510}, {LONG (wnd.interf_.right_size_ / 3), 30}, EVEC * 90, EVEC * 255},

        new BasicButton{{wnd.width_, 30              }, {wnd.interf_.right_size_, 30}, EVEC * 70, EVEC * 255, "Create"},
        new BasicButton{{wnd.width_, wnd.height_ - 30}, {wnd.interf_.right_size_, 30}, EVEC * 70, EVEC * 255, "Delete"},
    };
    Textbox editTextBoxes[] = {
        {{wnd.width_ + LONG (wnd.interf_.right_size_ / 3),      60}, {LONG (wnd.interf_.right_size_ / 3), 30}, "Coords"},
        {{wnd.width_ + LONG (wnd.interf_.right_size_ / 3 - 30), 90 }, {30, 30}, "X:"},
        {{wnd.width_ + LONG (wnd.interf_.right_size_ / 3 - 30), 120}, {30, 30}, "Y:"},
        {{wnd.width_ + LONG (wnd.interf_.right_size_ / 3 - 30), 150}, {30, 30}, "Z:"},
        {{wnd.width_ + LONG (wnd.interf_.right_size_ / 3),      180}, {LONG (wnd.interf_.right_size_ / 3), 30}, "Rotation"},
        {{wnd.width_ + LONG (wnd.interf_.right_size_ / 3 - 30), 210}, {30, 30}, "X:"},
        {{wnd.width_ + LONG (wnd.interf_.right_size_ / 3 - 30), 240}, {30, 30}, "Y:"},
        {{wnd.width_ + LONG (wnd.interf_.right_size_ / 3 - 30), 270}, {30, 30}, "Z:"},
        {{wnd.width_ + LONG (wnd.interf_.right_size_ / 3),      300}, {LONG (wnd.interf_.right_size_ / 3), 30}, "Size"},
        {{wnd.width_ + LONG (wnd.interf_.right_size_ / 3 - 30), 330}, {30, 30}, "X:"},
        {{wnd.width_ + LONG (wnd.interf_.right_size_ / 3 - 30), 360}, {30, 30}, "Y:"},
        {{wnd.width_ + LONG (wnd.interf_.right_size_ / 3 - 30), 390}, {30, 30}, "Z:"},
        {{wnd.width_ + LONG (wnd.interf_.right_size_ / 3),      420}, {LONG (wnd.interf_.right_size_ / 3), 30}, "Color"},
        {{wnd.width_ + LONG (wnd.interf_.right_size_ / 3 - 30), 450}, {30, 30}, "R:"},
        {{wnd.width_ + LONG (wnd.interf_.right_size_ / 3 - 30), 480}, {30, 30}, "G:"},
        {{wnd.width_ + LONG (wnd.interf_.right_size_ / 3 - 30), 510}, {30, 30}, "B:"}

    };

    Field fields[] = {
        {1, LEN(menuButtons), 0,                  menuButtons, nullptr},
        {0, LEN(editButtons), LEN(editTextBoxes), editButtons, editTextBoxes}
    };

    wnd.interf_.field_count_ = LEN(fields);
    wnd.interf_.fields_ = fields;

    start();
}

void Edit() {
    wnd.interf_.fields_[1].visible_ = !wnd.interf_.fields_[1].visible_;
    //wnd.interf_.fields_[2].visible_ = false;
    //wnd.interf_.fields_[3].visible_ = false;

    wnd.interf_.fields_[0].buttons_[0]->status_ = 3;
    wnd.interf_.fields_[0].buttons_[1]->status_ = 0;
    wnd.interf_.fields_[0].buttons_[2]->status_ = 0;

    wnd.interf_.draw(wnd);
}

void Objects() {
    wnd.interf_.fields_[1].visible_ = false;
    //wnd.interf_.fields_[2].visible_ = !wnd.interf_.fields_[2].visible_;
    //wnd.interf_.fields_[3].visible_ = false;

    wnd.interf_.fields_[0].buttons_[0]->status_ = 0;
    wnd.interf_.fields_[0].buttons_[1]->status_ = 3;
    wnd.interf_.fields_[0].buttons_[2]->status_ = 0;

    wnd.interf_.draw(wnd);
}

void Settings() {
    wnd.interf_.fields_[1].visible_ = false;
    //wnd.interf_.fields_[2].visible_ = false;
    //wnd.interf_.fields_[3].visible_ = !wnd.interf_.fields_[3].visible_;

    wnd.interf_.fields_[0].buttons_[0]->status_ = 0;
    wnd.interf_.fields_[0].buttons_[1]->status_ = 0;
    wnd.interf_.fields_[0].buttons_[2]->status_ = 3;

    wnd.interf_.draw(wnd);
}

void Save() {

}

void Load() {

}

void Screenshot() {
    HDC save = txCreateCompatibleDC(wnd.width_, wnd.height_);

    if (bitBlt(save, 0, 0, wnd.width_, wnd.height_)) {
        std::string PATH = std::string("screenshots/") + getTime() + std::string(".jpg");

        txSaveImage(PATH.c_str(), save);
    }

    txDeleteDC(save);
}

void Exit() {
    wnd.should_close_ = true;
}

std::string getTime() {
    time_t seconds = time(NULL);
    tm* timeinfo = localtime(&seconds);

    return std::to_string(timeinfo->tm_year) + std::to_string(timeinfo->tm_mon + 1) + std::to_string(timeinfo->tm_mday) +
           std::to_string(timeinfo->tm_hour) + std::to_string(timeinfo->tm_min)     + std::to_string(timeinfo->tm_sec);
}