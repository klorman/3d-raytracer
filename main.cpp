#include "TXLib.h"
#include "Window.hpp"
#include "Raytracer.hpp"
#include "Camera.hpp"

#include <ctime>
#include <clocale>

#define LEN(arr) sizeof(arr) / sizeof(arr[0])

std::string getTime();

void Edit();
void Objects();
void Settings();
void Create();
void Delete();
void SaveSettings();
void SelectObj();

void Save();
void Load();
void Screenshot();
void Exit();

void ScrollUp();
void ScrollDown();
void Thumb();
void Scroll(int offset);

Window wnd(800, 600, 50, 300, 400, 300);
Raytracer rt;
Camera cam(100, {0, 0, 0}, {0, 0, 1}, {0, 0, 0});

int objectSelected = 0;

void start();
bool getInput();
void createFields();

void createMenuField();
void createBottomMenuField();
void createEditField();
void createObjectsField();
void createSettingsField();
void createCreateField();
void createDeleteField();
void createCreateTextbox();
void createScrollBar();
void createCreateObjectField();

void createSphere();
void createCube();
void createPlane();

void start() {
    int frames = 0;

    while (!wnd.should_close_) { 
        if (isClosed()) break;
        if (!isForeground()) continue;

        bool moved = getInput();

        moved ? frames = 0 : ++frames;

        wnd.update(rt, cam, frames);
    }
}

bool getInput() {
    bool moved = false;
    static double prevFOV = 0;

    moved |= cam.move(wnd);

    if (moved) {
        reinterpret_cast<BasicButton*>(wnd.interf_.fields_[7].buttons_[0])->text_ = std::to_string(int (cam.pos_.x_ * reinterpret_cast<TextButton*>(wnd.interf_.fields_[7].buttons_[0])->mult_));
        reinterpret_cast<BasicButton*>(wnd.interf_.fields_[7].buttons_[1])->text_ = std::to_string(int (cam.pos_.y_ * reinterpret_cast<TextButton*>(wnd.interf_.fields_[7].buttons_[1])->mult_));
        reinterpret_cast<BasicButton*>(wnd.interf_.fields_[7].buttons_[2])->text_ = std::to_string(int (cam.pos_.z_ * reinterpret_cast<TextButton*>(wnd.interf_.fields_[7].buttons_[2])->mult_));

        reinterpret_cast<BasicButton*>(wnd.interf_.fields_[7].buttons_[3])->text_ = std::to_string(int (cam.angle_.x_ * reinterpret_cast<TextButton*>(wnd.interf_.fields_[7].buttons_[3])->mult_) % 360);
        reinterpret_cast<BasicButton*>(wnd.interf_.fields_[7].buttons_[4])->text_ = std::to_string(int (cam.angle_.y_ * reinterpret_cast<TextButton*>(wnd.interf_.fields_[7].buttons_[4])->mult_) % 360);
        reinterpret_cast<BasicButton*>(wnd.interf_.fields_[7].buttons_[5])->text_ = std::to_string(int (cam.angle_.z_ * reinterpret_cast<TextButton*>(wnd.interf_.fields_[7].buttons_[5])->mult_) % 360);

        for (int button = 0; button < wnd.interf_.fields_[7].button_count_; ++button) {
            wnd.interf_.fields_[7].buttons_[button]->draw(wnd.interf_.fields_[7].canvas_);
        }
    } 

    if ((int) prop.FOV != (int) prevFOV) {
        wnd.distToScreen = wnd.canvas_width_ / tan(prop.FOV * txPI / 360);

        prevFOV = prop.FOV;

        moved = true;
    }

    int selected = wnd.selectObject(rt, cam);

    if (selected) {
        objectSelected = selected - 1;
        Edit();

        moved = true;
    }

    return moved;
}

void createMenuField() {
    wnd.interf_.fields_[0].addButton(new BasicButton{{0                                     , 0          }, {LONG (wnd.interf_.right_size_ / 3), 30}, EVEC * 70, EVEC * 255, "Edit",       Edit});
    wnd.interf_.fields_[0].addButton(new BasicButton{{LONG (wnd.interf_.right_size_ / 3)    , 0          }, {LONG (wnd.interf_.right_size_ / 3), 30}, EVEC * 70, EVEC * 255, "Objects",    Objects});
    wnd.interf_.fields_[0].addButton(new BasicButton{{LONG (wnd.interf_.right_size_ / 3) * 2, 0          }, {LONG (wnd.interf_.right_size_ / 3), 30}, EVEC * 70, EVEC * 255, "Settings",   Settings});
    wnd.interf_.fields_[0].addButton(new BasicButton{{0                                     , wnd.height_}, {LONG (wnd.interf_.right_size_ / 3), 50}, EVEC * 70, EVEC * 255, "Save",       Save});
    wnd.interf_.fields_[0].addButton(new BasicButton{{LONG (wnd.interf_.right_size_ / 3)    , wnd.height_}, {LONG (wnd.interf_.right_size_ / 3), 50}, EVEC * 70, EVEC * 255, "Load",       Load});
    wnd.interf_.fields_[0].addButton(new BasicButton{{LONG (wnd.interf_.right_size_ / 3) * 2, wnd.height_}, {LONG (wnd.interf_.right_size_ / 3), 50}, EVEC * 70, EVEC * 255, "Save Image", Screenshot});
    //wnd.interf_.fields_[0].addButton(new BasicButton{{LONG (wnd.interf_.right_size_ / 4) * 3, wnd.height_}, {LONG (wnd.interf_.right_size_ / 4), 50}, EVEC * 70, EVEC * 255, "Exit",       Exit});
}

void createBottomMenuField() {
    wnd.interf_.fields_[7].addButton(new TextButton {&cam.pos_.x_,   -1, {58 , 25}, {75, 25}, EVEC * 90, EVEC * 255});
    wnd.interf_.fields_[7].addButton(new TextButton {&cam.pos_.y_,   -1, {191, 25}, {75, 25}, EVEC * 90, EVEC * 255});
    wnd.interf_.fields_[7].addButton(new TextButton {&cam.pos_.z_,   -1, {324, 25}, {75, 25}, EVEC * 90, EVEC * 255});
    wnd.interf_.fields_[7].addButton(new TextButton {&cam.angle_.x_, -1, {458, 25}, {75, 25}, EVEC * 90, EVEC * 255, 0, 360, int (180 / txPI)});
    wnd.interf_.fields_[7].addButton(new TextButton {&cam.angle_.y_, -1, {591, 25}, {75, 25}, EVEC * 90, EVEC * 255, 0, 360, int (180 / txPI)});
    wnd.interf_.fields_[7].addButton(new TextButton {&cam.angle_.z_, -1, {724, 25}, {75, 25}, EVEC * 90, EVEC * 255, 0, 360, int (180 / txPI)});

    wnd.interf_.fields_[7].addTextbox({{0  , 0 }, {400, 25}, "Coords",   prop.INTERFACECOLOR});
    wnd.interf_.fields_[7].addTextbox({{0  , 25}, {58 , 25}, "X:",       -EVEC, EVEC * 150, DT_CENTER | DT_VCENTER});
    wnd.interf_.fields_[7].addTextbox({{133, 25}, {58 , 25}, "Y:",       -EVEC, EVEC * 150, DT_CENTER | DT_VCENTER});
    wnd.interf_.fields_[7].addTextbox({{266, 25}, {58 , 25}, "Z:",       -EVEC, EVEC * 150, DT_CENTER | DT_VCENTER});
    wnd.interf_.fields_[7].addTextbox({{400, 0 }, {400, 25}, "Rotation", prop.INTERFACECOLOR});
    wnd.interf_.fields_[7].addTextbox({{400, 25}, {58 , 25}, "X:",       -EVEC, EVEC * 150, DT_CENTER | DT_VCENTER});
    wnd.interf_.fields_[7].addTextbox({{533, 25}, {58 , 25}, "Y:",       -EVEC, EVEC * 150, DT_CENTER | DT_VCENTER});
    wnd.interf_.fields_[7].addTextbox({{666, 25}, {58 , 25}, "Z:",       -EVEC, EVEC * 150, DT_CENTER | DT_VCENTER});
}

void createEditField() {
    wnd.interf_.fields_[1].addButton(new TextButton {nullptr, posX,     {LONG ((wnd.interf_.right_size_ - 20) / 2), 30 }, {LONG ((wnd.interf_.right_size_ - 20) / 2), 30}, EVEC * 90, EVEC * 255});
    wnd.interf_.fields_[1].addButton(new TextButton {nullptr, posY,     {LONG ((wnd.interf_.right_size_ - 20) / 2), 60 }, {LONG ((wnd.interf_.right_size_ - 20) / 2), 30}, EVEC * 90, EVEC * 255});
    wnd.interf_.fields_[1].addButton(new TextButton {nullptr, posZ,     {LONG ((wnd.interf_.right_size_ - 20) / 2), 90 }, {LONG ((wnd.interf_.right_size_ - 20) / 2), 30}, EVEC * 90, EVEC * 255});
    wnd.interf_.fields_[1].addButton(new TextButton {nullptr, rotX,     {LONG ((wnd.interf_.right_size_ - 20) / 2), 150}, {LONG ((wnd.interf_.right_size_ - 20) / 2), 30}, EVEC * 90, EVEC * 255});
    wnd.interf_.fields_[1].addButton(new TextButton {nullptr, rotY,     {LONG ((wnd.interf_.right_size_ - 20) / 2), 180}, {LONG ((wnd.interf_.right_size_ - 20) / 2), 30}, EVEC * 90, EVEC * 255});
    wnd.interf_.fields_[1].addButton(new TextButton {nullptr, rotZ,     {LONG ((wnd.interf_.right_size_ - 20) / 2), 210}, {LONG ((wnd.interf_.right_size_ - 20) / 2), 30}, EVEC * 90, EVEC * 255});
    wnd.interf_.fields_[1].addButton(new TextButton {nullptr, szX ,     {LONG ((wnd.interf_.right_size_ - 20) / 2), 270}, {LONG ((wnd.interf_.right_size_ - 20) / 2), 30}, EVEC * 90, EVEC * 255, 1});
    wnd.interf_.fields_[1].addButton(new TextButton {nullptr, szY ,     {LONG ((wnd.interf_.right_size_ - 20) / 2), 300}, {LONG ((wnd.interf_.right_size_ - 20) / 2), 30}, EVEC * 90, EVEC * 255, 1});
    wnd.interf_.fields_[1].addButton(new TextButton {nullptr, szZ ,     {LONG ((wnd.interf_.right_size_ - 20) / 2), 330}, {LONG ((wnd.interf_.right_size_ - 20) / 2), 30}, EVEC * 90, EVEC * 255, 1});
    wnd.interf_.fields_[1].addButton(new TextButton {nullptr, colX,     {LONG ((wnd.interf_.right_size_ - 20) / 2), 390}, {LONG ((wnd.interf_.right_size_ - 20) / 2), 30}, EVEC * 90, EVEC * 255, 0, 255, 255});
    wnd.interf_.fields_[1].addButton(new TextButton {nullptr, colY,     {LONG ((wnd.interf_.right_size_ - 20) / 2), 420}, {LONG ((wnd.interf_.right_size_ - 20) / 2), 30}, EVEC * 90, EVEC * 255, 0, 255, 255});
    wnd.interf_.fields_[1].addButton(new TextButton {nullptr, colZ,     {LONG ((wnd.interf_.right_size_ - 20) / 2), 450}, {LONG ((wnd.interf_.right_size_ - 20) / 2), 30}, EVEC * 90, EVEC * 255, 0, 255, 255});
    wnd.interf_.fields_[1].addButton(new TextButton {nullptr, matRefl,  {LONG ((wnd.interf_.right_size_ - 20) / 2), 510}, {LONG ((wnd.interf_.right_size_ - 20) / 2), 30}, EVEC * 90, EVEC * 255, 0, 100, 100});
    wnd.interf_.fields_[1].addButton(new TextButton {nullptr, matRefr,  {LONG ((wnd.interf_.right_size_ - 20) / 2), 540}, {LONG ((wnd.interf_.right_size_ - 20) / 2), 30}, EVEC * 90, EVEC * 255, 1, INF, 100});
    wnd.interf_.fields_[1].addButton(new TextButton {nullptr, matTr,    {LONG ((wnd.interf_.right_size_ - 20) / 2), 570}, {LONG ((wnd.interf_.right_size_ - 20) / 2), 30}, EVEC * 90, EVEC * 255, 0, 100, 100});
    wnd.interf_.fields_[1].addButton(new TextButton {nullptr, matRough, {LONG ((wnd.interf_.right_size_ - 20) / 2), 600}, {LONG ((wnd.interf_.right_size_ - 20) / 2), 30}, EVEC * 90, EVEC * 255, 0, 100, 100});

    wnd.interf_.fields_[1].addTextbox({{0,  0},   {       wnd.interf_.right_size_ - 20,            30}, "Coords",        prop.INTERFACECOLOR});
    wnd.interf_.fields_[1].addTextbox({{10, 30 }, {LONG ((wnd.interf_.right_size_ - 20) / 2) - 20, 30}, "X:",            -EVEC, EVEC * 150, DT_LEFT | DT_VCENTER});
    wnd.interf_.fields_[1].addTextbox({{10, 60 }, {LONG ((wnd.interf_.right_size_ - 20) / 2) - 20, 30}, "Y:",            -EVEC, EVEC * 150, DT_LEFT | DT_VCENTER});
    wnd.interf_.fields_[1].addTextbox({{10, 90 }, {LONG ((wnd.interf_.right_size_ - 20) / 2) - 20, 30}, "Z:",            -EVEC, EVEC * 150, DT_LEFT | DT_VCENTER});
    wnd.interf_.fields_[1].addTextbox({{0,  120}, {       wnd.interf_.right_size_ - 20,            30}, "Rotation",      prop.INTERFACECOLOR});
    wnd.interf_.fields_[1].addTextbox({{10, 150}, {LONG ((wnd.interf_.right_size_ - 20) / 2) - 20, 30}, "X:",            -EVEC, EVEC * 150, DT_LEFT | DT_VCENTER});
    wnd.interf_.fields_[1].addTextbox({{10, 180}, {LONG ((wnd.interf_.right_size_ - 20) / 2) - 20, 30}, "Y:",            -EVEC, EVEC * 150, DT_LEFT | DT_VCENTER});
    wnd.interf_.fields_[1].addTextbox({{10, 210}, {LONG ((wnd.interf_.right_size_ - 20) / 2) - 20, 30}, "Z:",            -EVEC, EVEC * 150, DT_LEFT | DT_VCENTER});
    wnd.interf_.fields_[1].addTextbox({{0,  240}, {       wnd.interf_.right_size_ - 20,            30}, "Size",          prop.INTERFACECOLOR});
    wnd.interf_.fields_[1].addTextbox({{10, 270}, {LONG ((wnd.interf_.right_size_ - 20) / 2) - 20, 30}, "X:",            -EVEC, EVEC * 150, DT_LEFT | DT_VCENTER});
    wnd.interf_.fields_[1].addTextbox({{10, 300}, {LONG ((wnd.interf_.right_size_ - 20) / 2) - 20, 30}, "Y:",            -EVEC, EVEC * 150, DT_LEFT | DT_VCENTER});
    wnd.interf_.fields_[1].addTextbox({{10, 330}, {LONG ((wnd.interf_.right_size_ - 20) / 2) - 20, 30}, "Z:",            -EVEC, EVEC * 150, DT_LEFT | DT_VCENTER});
    wnd.interf_.fields_[1].addTextbox({{0,  360}, {       wnd.interf_.right_size_ - 20,            30}, "Color",         prop.INTERFACECOLOR});
    wnd.interf_.fields_[1].addTextbox({{10, 390}, {LONG ((wnd.interf_.right_size_ - 20) / 2) - 20, 30}, "R:",            -EVEC, EVEC * 150, DT_LEFT | DT_VCENTER});
    wnd.interf_.fields_[1].addTextbox({{10, 420}, {LONG ((wnd.interf_.right_size_ - 20) / 2) - 20, 30}, "G:",            -EVEC, EVEC * 150, DT_LEFT | DT_VCENTER});
    wnd.interf_.fields_[1].addTextbox({{10, 450}, {LONG ((wnd.interf_.right_size_ - 20) / 2) - 20, 30}, "B:",            -EVEC, EVEC * 150, DT_LEFT | DT_VCENTER});
    wnd.interf_.fields_[1].addTextbox({{0,  480}, {       wnd.interf_.right_size_ - 20,            30}, "Material",      prop.INTERFACECOLOR});
    wnd.interf_.fields_[1].addTextbox({{10, 510}, {LONG ((wnd.interf_.right_size_ - 20) / 2) - 20, 30}, "reflection:  ", -EVEC, EVEC * 150, DT_LEFT | DT_VCENTER});
    wnd.interf_.fields_[1].addTextbox({{10, 540}, {LONG ((wnd.interf_.right_size_ - 20) / 2) - 20, 30}, "n:           ", -EVEC, EVEC * 150, DT_LEFT | DT_VCENTER});
    wnd.interf_.fields_[1].addTextbox({{10, 570}, {LONG ((wnd.interf_.right_size_ - 20) / 2) - 20, 30}, "transparency:", -EVEC, EVEC * 150, DT_LEFT | DT_VCENTER});
    wnd.interf_.fields_[1].addTextbox({{10, 600}, {LONG ((wnd.interf_.right_size_ - 20) / 2) - 20, 30}, "smoothness:  ", -EVEC, EVEC * 150, DT_LEFT | DT_VCENTER});
    //wnd.interf_.fields_[1].addTextbox({{LONG (wnd.interf_.right_size_ / 3 - 30), 991}, {30, 30}, "A:"});
}

void createObjectsField() {
    for (int obj = 0; obj < rt.object_count_; ++obj) {
        wnd.interf_.fields_[2].addButton(new BasicButton{{0,                                      50 * obj}, {wnd.interf_.right_size_ - 20,            50}, -EVEC,    -EVEC,       "",    SelectObj});
        wnd.interf_.fields_[2].addButton(new BasicButton{{0,                                      50 * obj}, {LONG (wnd.interf_.right_size_ / 3 * 2),  50}, EVEC * 70, EVEC * 255, std::to_string(rt.objects_[obj]->type)});
        wnd.interf_.fields_[2].addButton(new BasicButton{{LONG (wnd.interf_.right_size_ / 3 * 2), 50 * obj}, {LONG (wnd.interf_.right_size_ / 3 - 20), 50}, EVEC * 70, EVEC * 255, "Del", Delete});
    }
}

void createSettingsField() {
    wnd.interf_.fields_[3].addButton(new TextButton {&prop.UPSCALING,          -1, {LONG (wnd.interf_.right_size_ / 3 * 2), 0  }, {LONG (wnd.interf_.right_size_ / 3), 30}, EVEC * 90, EVEC * 255, 1, 16});
    wnd.interf_.fields_[3].addButton(new TextButton {&prop.BACKGROUNDCOLOR.x_, -1, {LONG (wnd.interf_.right_size_ / 3 * 2), 30 }, {LONG (wnd.interf_.right_size_ / 3), 30}, EVEC * 90, EVEC * 255, 0, 255, 255});
    wnd.interf_.fields_[3].addButton(new TextButton {&prop.BACKGROUNDCOLOR.y_, -1, {LONG (wnd.interf_.right_size_ / 3 * 2), 60 }, {LONG (wnd.interf_.right_size_ / 3), 30}, EVEC * 90, EVEC * 255, 0, 255, 255});
    wnd.interf_.fields_[3].addButton(new TextButton {&prop.BACKGROUNDCOLOR.z_, -1, {LONG (wnd.interf_.right_size_ / 3 * 2), 90 }, {LONG (wnd.interf_.right_size_ / 3), 30}, EVEC * 90, EVEC * 255, 0, 255, 255});
    wnd.interf_.fields_[3].addButton(new TextButton {&prop.MAXGEN,             -1, {LONG (wnd.interf_.right_size_ / 3 * 2), 120}, {LONG (wnd.interf_.right_size_ / 3), 30}, EVEC * 90, EVEC * 255, 1});
    wnd.interf_.fields_[3].addButton(new TextButton {&prop.FOV,                -1, {LONG (wnd.interf_.right_size_ / 3 * 2), 150}, {LONG (wnd.interf_.right_size_ / 3), 30}, EVEC * 90, EVEC * 255, 1, 179});
    wnd.interf_.fields_[3].addButton(new TextButton {&prop.FOCUS,              -1, {LONG (wnd.interf_.right_size_ / 3 * 2), 180}, {LONG (wnd.interf_.right_size_ / 3), 30}, EVEC * 90, EVEC * 255, 0});
    wnd.interf_.fields_[3].addButton(new TextButton {&prop.BLURRADIUS,         -1, {LONG (wnd.interf_.right_size_ / 3 * 2), 210}, {LONG (wnd.interf_.right_size_ / 3), 30}, EVEC * 90, EVEC * 255, 0});

    wnd.interf_.fields_[3].addButton(new BasicButton{{0, wnd.height_ - 60}, {wnd.interf_.right_size_, 30}, EVEC * 70, EVEC * 255, "Save settings", SaveSettings});
    
    wnd.interf_.fields_[3].addTextbox({{0, 0  }, {LONG (wnd.interf_.right_size_ / 3 * 2), 30}, "UPSCALING"       , prop.INTERFACECOLOR, EVEC * 255, DT_CENTER | DT_VCENTER});
    wnd.interf_.fields_[3].addTextbox({{0, 30 }, {LONG (wnd.interf_.right_size_ / 3 * 2), 90}, "BACKGROUND COLOR", prop.INTERFACECOLOR, EVEC * 255, DT_CENTER | DT_VCENTER});
    wnd.interf_.fields_[3].addTextbox({{0, 120}, {LONG (wnd.interf_.right_size_ / 3 * 2), 30}, "MAXGEN",           prop.INTERFACECOLOR, EVEC * 255, DT_CENTER | DT_VCENTER});
    wnd.interf_.fields_[3].addTextbox({{0, 150}, {LONG (wnd.interf_.right_size_ / 3 * 2), 30}, "FOV",              prop.INTERFACECOLOR, EVEC * 255, DT_CENTER | DT_VCENTER});
    wnd.interf_.fields_[3].addTextbox({{0, 180}, {LONG (wnd.interf_.right_size_ / 3 * 2), 30}, "FOCUS",            prop.INTERFACECOLOR, EVEC * 255, DT_CENTER | DT_VCENTER});
    wnd.interf_.fields_[3].addTextbox({{0, 210}, {LONG (wnd.interf_.right_size_ / 3 * 2), 30}, "BLURRADIUS",       prop.INTERFACECOLOR, EVEC * 255, DT_CENTER | DT_VCENTER});
}

void createCreateField() {
    wnd.interf_.fields_[4].addButton(new BasicButton{{0, 0}, {wnd.interf_.right_size_, 30}, EVEC * 70, EVEC * 255, "Create", Create});
}

void createDeleteField() {
    wnd.interf_.fields_[5].addButton(new BasicButton{{0, 0}, {wnd.interf_.right_size_, 30}, EVEC * 70, EVEC * 255, "Delete", Delete});
}

void createCreateTextbox() {
    wnd.interf_.fields_[6].addTextbox({{0, 0}, {wnd.interf_.right_size_, 30}, "Create or select an object", -EVEC, EVEC * 150, DT_CENTER | DT_VCENTER});  
}

void createCreateObjectField() {
    wnd.interf_.fields_[9].addButton(new BasicButton{{0, 0 }, {wnd.interf_.right_size_, 30}, EVEC * 70, EVEC * 255, "Create Sphere", createSphere});
    wnd.interf_.fields_[9].addButton(new BasicButton{{0, 30}, {wnd.interf_.right_size_, 30}, EVEC * 70, EVEC * 255, "Create Box"   , createCube  });
    wnd.interf_.fields_[9].addButton(new BasicButton{{0, 60}, {wnd.interf_.right_size_, 30}, EVEC * 70, EVEC * 255, "Create Plane" , createPlane });
}

void createSphere() {
    rt.addObject(new Sphere {{ 0.9, 1.0, 0.0, 1.0  }, 50, { 0, 0, 0 }, { 1.0, 1.0, 1.0 }});
    
    Create();
}

void createCube() {
    rt.addObject(new Box    {{ 0.9, 1.0, 0.0, 1.0  }, 50, { 0, 0, 0 }, { 1.0, 1.0, 1.0 }});

    Create();
}

void createPlane() {
    rt.addObject(new Plane  {{ 0.9, 1.0, 0.0, 1.0  }, 50, { 0, 0, 0 }, { 1.0, 1.0, 1.0 }});

    Create();
}

void createScrollBar() {
    wnd.interf_.fields_[8].buttons_.clear();
    wnd.interf_.fields_[8].button_count_ = 0;

    txDeleteDC(wnd.interf_.fields_[8].canvas_);
    wnd.interf_.fields_[8].canvas_ = txCreateCompatibleDC(wnd.interf_.fields_[8].size_.x, wnd.interf_.fields_[8].size_.y);

    wnd.interf_.fields_[8].addButton(new BasicButton{{0, 0                                  }, {20, 20},                                  EVEC * 90, EVEC * 255, "-", ScrollUp});
    wnd.interf_.fields_[8].addButton(new BasicButton{{0, wnd.interf_.fields_[8].size_.y - 20}, {20, 20},                                  EVEC * 90, EVEC * 255, "-", ScrollDown});
    wnd.interf_.fields_[8].addButton(new BasicButton{{0, 20                                 }, {20, wnd.interf_.fields_[8].size_.y - 40}, EVEC * 90, EVEC * 255, "",  nullptr, Thumb});

    for (int button = 0; button < wnd.interf_.fields_[8].button_count_; ++button) {
        wnd.interf_.fields_[8].buttons_[button]->fieldCoords_ = wnd.interf_.fields_[8].pos_;
        wnd.interf_.fields_[8].buttons_[button]->fieldSize_   = wnd.interf_.fields_[8].size_;
    }
}

void createFields() {
    wnd.interf_.fields_.clear();
    wnd.interf_.field_count_ = 0;

    wnd.interf_.addField(1, {wnd.width_                               , 0                     }, {wnd.interf_.right_size_, wnd.height_ + wnd.interf_.bottom_size_}); //right menu
    wnd.interf_.addField(1, {wnd.width_                               , 60                    }, {wnd.interf_.right_size_, wnd.height_ - 90                      }); //edit
    wnd.interf_.addField(0, {wnd.width_                               , 30                    }, {wnd.interf_.right_size_, wnd.height_ - 30                      }); //objects
    wnd.interf_.addField(0, {wnd.width_                               , 30                    }, {wnd.interf_.right_size_, wnd.height_ - 30                      }); //settings
    wnd.interf_.addField(1, {wnd.width_                               , 30                    }, {wnd.interf_.right_size_, 30                                    }); //create   <--|
    wnd.interf_.addField(0, {wnd.width_                               , wnd.height_ - 30      }, {wnd.interf_.right_size_, 30                                    }); //delete   <--|---- ??? хотя мб и нормально?
    wnd.interf_.addField(1, {wnd.width_                               , LONG (wnd.height_ / 2)}, {wnd.interf_.right_size_, 30                                    }); //textbox  <--|
    wnd.interf_.addField(1, {0                                        , wnd.height_           }, {wnd.width_,              wnd.interf_.bottom_size_              }); //bottom menu
    wnd.interf_.addField(0, {wnd.width_ + wnd.interf_.right_size_ - 20, 60                    }, {20,                      wnd.height_ - 90                      }); //scrollbar нужно сделать для каждого поля свой скроллбар, но пока пусть будет так
    wnd.interf_.addField(0, {wnd.width_                               , 30                    }, {wnd.interf_.right_size_, 90                                    }); //createObject
    
    createMenuField();
    createBottomMenuField();
    createEditField();
    createObjectsField();
    createSettingsField();
    createCreateField();     
    createDeleteField();
    createCreateTextbox();
    createScrollBar();
    createCreateObjectField();

    for (int field = 0; field < wnd.interf_.field_count_; ++field) {
        wnd.interf_.fields_[field].canvas_ = txCreateCompatibleDC(wnd.interf_.fields_[field].canvas_size_.x,  wnd.interf_.fields_[field].canvas_size_.y);
        txSelectFont("Consolas", 20, false, FW_BOLD, false, false, false, 0, wnd.interf_.fields_[field].canvas_);

        for (int button = 0; button < wnd.interf_.fields_[field].button_count_; ++button) {
            wnd.interf_.fields_[field].buttons_[button]->fieldCoords_ = wnd.interf_.fields_[field].pos_;
            wnd.interf_.fields_[field].buttons_[button]->fieldSize_   = wnd.interf_.fields_[field].size_;
        }
    }

    Edit();
    //wnd.interf_.draw();                                                                                                                            
}

void ScrollUp() {
    int offset = 10;

    int prev = wnd.interf_.fields_[8].buttons_[2]->wndPos_.y;

    wnd.interf_.fields_[8].buttons_[2]->wndPos_.y = std::max(wnd.interf_.fields_[8].pos_.y + 20, wnd.interf_.fields_[8].buttons_[2]->wndPos_.y - offset);

    offset = wnd.interf_.fields_[8].buttons_[2]->wndPos_.y - prev;
    
    if (offset != 0) {
        Scroll(offset);
    }

    //wnd.interf_.fields_[8].draw();
    //copyToWnd(wnd.interf_.fields_[8].canvas_, wnd.interf_.fields_[8].pos_.x, wnd.interf_.fields_[8].pos_.y, wnd.interf_.fields_[8].size_.x, wnd.interf_.fields_[8].size_.y);
}

void ScrollDown() {
    int offset = -10;

    int prev = wnd.interf_.fields_[8].buttons_[2]->wndPos_.y;

    wnd.interf_.fields_[8].buttons_[2]->wndPos_.y = std::min(wnd.interf_.fields_[8].pos_.y + wnd.interf_.fields_[8].size_.y - wnd.interf_.fields_[8].buttons_[2]->size_.y - 20, wnd.interf_.fields_[8].buttons_[2]->wndPos_.y + 10);

    offset = wnd.interf_.fields_[8].buttons_[2]->wndPos_.y - prev;
    
    if (offset != 0) {
        Scroll(offset);
    }

    //wnd.interf_.fields_[8].draw();
    //copyToWnd(wnd.interf_.fields_[8].canvas_, wnd.interf_.fields_[8].pos_.x, wnd.interf_.fields_[8].pos_.y, wnd.interf_.fields_[8].size_.x, wnd.interf_.fields_[8].size_.y);
}

void Thumb() {
    POINT pos1 = mousePos(), pos2 = {0, 0};

    //txBegin();

    while(GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
        pos2 = mousePos();

        int offset = pos2.y - pos1.y;

        if (offset != 0) {
            int prev = wnd.interf_.fields_[8].buttons_[2]->wndPos_.y;

            wnd.interf_.fields_[8].buttons_[2]->wndPos_.y = std::max(wnd.interf_.fields_[8].pos_.y + 20, std::min(wnd.interf_.fields_[8].pos_.y + wnd.interf_.fields_[8].size_.y - wnd.interf_.fields_[8].buttons_[2]->size_.y - 20, wnd.interf_.fields_[8].buttons_[2]->wndPos_.y + offset));
            
            offset = wnd.interf_.fields_[8].buttons_[2]->wndPos_.y - prev;

            if (offset != 0) {
                Scroll(offset);

                pos1 = pos2;
            }
        }

    //txEnd();
        
    }
}

void Scroll(int offset) { //работает не совсем корректно, нужно сделать свою структуру POINT, в которой хранятся нецелые цисла (POFLOAT? PODOUBLE?), чтобы хранить координаты и размер кнопок, полей
    setColor    (VEC2RGB((prop.INTERFACECOLOR * 0.9)), 1);
    setFillColor(VEC2RGB(prop.INTERFACECOLOR));
    rectangle   (wnd.interf_.fields_[8].pos_.x, wnd.interf_.fields_[8].pos_.y + 20, wnd.interf_.fields_[8].pos_.x + 20, wnd.interf_.fields_[8].pos_.y + wnd.interf_.fields_[8].size_.y - 20);

    wnd.interf_.fields_[8].buttons_[2]->draw(wnd.interf_.fields_[8].canvas_);

    int field = 0;

    if      (wnd.interf_.fields_[1].visible_) field = 1;
    else if (wnd.interf_.fields_[2].visible_) field = 2;

    offset = std::min(wnd.interf_.fields_[field].canvas_size_.y - wnd.interf_.fields_[field].size_.y, LONG (wnd.interf_.fields_[8].size_.y * (wnd.interf_.fields_[8].buttons_[2]->wndPos_.y - wnd.interf_.fields_[8].pos_.y - 20.0) / wnd.interf_.fields_[8].buttons_[2]->size_.y));

    copyToWnd(wnd.interf_.fields_[field].canvas_, 
              wnd.interf_.fields_[field].pos_.x, 
              wnd.interf_.fields_[field].pos_.y, 
              wnd.interf_.fields_[field].size_.x, 
              wnd.interf_.fields_[field].size_.y, 
              0, 
              offset);

    for (int button = 0; button < wnd.interf_.fields_[field].button_count_; ++button) {
        wnd.interf_.fields_[field].buttons_[button]->wndPos_.y = wnd.interf_.fields_[field].pos_.y + wnd.interf_.fields_[field].buttons_[button]->fieldPos_.y - offset;
    }

    for (int textbox = 0; textbox < wnd.interf_.fields_[field].textbox_count_; ++textbox) {
        wnd.interf_.fields_[field].textboxes_[textbox].wndPos_.y = wnd.interf_.fields_[field].pos_.y + wnd.interf_.fields_[field].textboxes_[textbox].fieldPos_.y - offset;
    }
}

int main() {
    rt.addObject(new Sphere {{ 0.0, 1.5, 0.9, 1.0  },     50      , { 300, 400, 60 }, { 1.0, 1.0, 1.0 }                            }); //прозрачный
    rt.addObject(new Sphere {{ 0.9, 1.0, 0.0, 1.0  },     50      , { 560, 400, 80 }, { 1.0, 1.0, 1.0 }                            }); //гладкий
    rt.addObject(new Sphere {{ 0.9, 1.0, 0.0, 1.0  }, {30, 30, 60}, { 600, 385, 10 }, { 1.0, 0.0, 0.0 }                            }); //гладкий
    rt.addObject(new Sphere {{ 0.9, 1.0, 0.0, 0.0  },     50      , { 400, 400, 100}, { 1.0, 1.0, 1.0 }                            }); //матовый
    rt.addObject(new Box    {{ 0.5, 1.5, 0.5, 0.0  }, {50, 20, 50}, {   0, 400, 200}, { 0.3, 0.3, 1.0 }, (Vector { 1, 1, 1}).norm()}); //прозрачный, матовый
    rt.addObject(new Plane  {{ 0.9, 1.0, 0.0, 0.1  }              , { 0  , 450, 0  }, { 1.0, 1.0, 0.0 }, { 0,-1, 0}                });
    rt.addObject(new Sphere {{ 0.0, 1.0,-1.0, 0.0  },     200     , { 300, 200,-200}, { 0.9, 0.9, 0.9 }                            }); //источник

    createFields();

    start();
}

void Edit() {
    if (objectSelected) {
        wnd.interf_.fields_[1].visible_ = true;
        wnd.interf_.fields_[4].visible_ = true;
        wnd.interf_.fields_[5].visible_ = true;
        wnd.interf_.fields_[6].visible_ = false;
        wnd.interf_.fields_[8].visible_ = true;
        wnd.interf_.fields_[9].visible_ = false;

        wnd.interf_.fields_[8].pos_  = {wnd.width_ + wnd.interf_.right_size_ - 20, 60};
        wnd.interf_.fields_[8].size_ = {20, wnd.height_ - 90};
        createScrollBar();

        for (int button = 0; button < wnd.interf_.fields_[1].button_count_; ++button) {                                                                    //
            wnd.interf_.fields_[1].buttons_[button]->wndPos_.y = wnd.interf_.fields_[1].buttons_[button]->fieldPos_.y + wnd.interf_.fields_[1].pos_.y;     //
        }                                                                                                                                                  //
                                                                                                                                                           // стоит вынести в функцию
        for (int textbox = 0; textbox < wnd.interf_.fields_[1].textbox_count_; ++textbox) {                                                                //
            wnd.interf_.fields_[1].textboxes_[textbox].wndPos_.y = wnd.interf_.fields_[1].textboxes_[textbox].fieldPos_.y + wnd.interf_.fields_[1].pos_.y; //
        }                                                                                                                                                  //
        
        wnd.interf_.fields_[8].buttons_[2]->size_.y = LONG ((wnd.interf_.fields_[8].size_.y - 40) * wnd.interf_.fields_[1].size_.y / wnd.interf_.fields_[1].canvas_size_.y);
    }

    else {
        wnd.interf_.fields_[1].visible_ = false;
        wnd.interf_.fields_[4].visible_ = true;
        wnd.interf_.fields_[5].visible_ = false;
        wnd.interf_.fields_[6].visible_ = true;
        wnd.interf_.fields_[8].visible_ = false;
        wnd.interf_.fields_[9].visible_ = false;
    }

    wnd.interf_.fields_[2].visible_ = false;
    wnd.interf_.fields_[3].visible_ = false;

    wnd.interf_.fields_[0].buttons_[0]->status_ = 3;
    wnd.interf_.fields_[0].buttons_[1]->status_ = 0;
    wnd.interf_.fields_[0].buttons_[2]->status_ = 0;

    wnd.interf_.draw();
}

void Objects() {
    wnd.interf_.fields_[1].visible_ = false;
    wnd.interf_.fields_[2].visible_ = true;
    wnd.interf_.fields_[3].visible_ = false;
    wnd.interf_.fields_[4].visible_ = false;
    wnd.interf_.fields_[5].visible_ = false;
    wnd.interf_.fields_[6].visible_ = false;
    wnd.interf_.fields_[8].visible_ = true;
    wnd.interf_.fields_[9].visible_ = false;

    wnd.interf_.fields_[8].pos_  = {wnd.width_ + wnd.interf_.right_size_ - 20, 30};
    wnd.interf_.fields_[8].size_ = {20, wnd.height_ - 30};
    createScrollBar();

    for (int button = 0; button < wnd.interf_.fields_[2].button_count_; ++button) {                                                                     //
        wnd.interf_.fields_[2].buttons_[button]->wndPos_.y = wnd.interf_.fields_[2].buttons_[button]->fieldPos_.y + wnd.interf_.fields_[2].pos_.y;      //
    }                                                                                                                                                   //
                                                                                                                                                        // стоит вынести в функцию
    for (int textbox = 0; textbox < wnd.interf_.fields_[2].textbox_count_; ++textbox) {                                                                 //
        wnd.interf_.fields_[2].textboxes_[textbox].wndPos_.y = wnd.interf_.fields_[2].textboxes_[textbox].fieldPos_.y + wnd.interf_.fields_[2].pos_.y;  //
    }                                                                                                                                                   //

    wnd.interf_.fields_[8].buttons_[2]->size_.y = LONG ((wnd.interf_.fields_[8].size_.y - 40) * wnd.interf_.fields_[2].size_.y / wnd.interf_.fields_[2].canvas_size_.y);

    wnd.interf_.fields_[0].buttons_[0]->status_ = 0;
    wnd.interf_.fields_[0].buttons_[1]->status_ = 3;
    wnd.interf_.fields_[0].buttons_[2]->status_ = 0;

    wnd.interf_.draw(); //холст всегда перерисовывается заново. надо перересовывать, когда удалется или создается новый объект, а здесь нужно копировать их холста в окно 
}

void Settings() {
    wnd.interf_.fields_[1].visible_ = false;
    wnd.interf_.fields_[2].visible_ = false;
    wnd.interf_.fields_[3].visible_ = true;
    wnd.interf_.fields_[4].visible_ = false;
    wnd.interf_.fields_[5].visible_ = false;
    wnd.interf_.fields_[6].visible_ = false;
    wnd.interf_.fields_[8].visible_ = false;
    wnd.interf_.fields_[9].visible_ = false;

    wnd.interf_.fields_[0].buttons_[0]->status_ = 0;
    wnd.interf_.fields_[0].buttons_[1]->status_ = 0;
    wnd.interf_.fields_[0].buttons_[2]->status_ = 3;

    wnd.interf_.draw();
}

void Create() {
    if (!wnd.interf_.fields_[9].visible_) {
        wnd.interf_.fields_[1].visible_ = false;
        wnd.interf_.fields_[2].visible_ = false;
        wnd.interf_.fields_[3].visible_ = false;
        wnd.interf_.fields_[4].visible_ = false;
        wnd.interf_.fields_[5].visible_ = false;
        wnd.interf_.fields_[6].visible_ = false;
        wnd.interf_.fields_[8].visible_ = false;
        wnd.interf_.fields_[9].visible_ = true;

        wnd.interf_.draw();

        return;
    }

    beginWnd();

    //rt.addObject(new Sphere {{ 0.9, 1.0, 0.0, 1.0  }, 50, { 0, 0, 0 }, { 1.0, 1.0, 1.0 }});

    for (int i = 0; i < rt.object_count_; ++i) rt.objects_[i]->status_ = false;
    rt.objects_.back()->status_ = true;

    createFields();

    wnd.bindButtonsToObject(rt.objects_.back());
    objectSelected = (int) rt.objects_.size();

    //createObjectsField();
    
    Edit();

    endWnd();

    //wnd.interf_.fields_[9].visible_ = false;
}

void Delete() {
    int id = objectSelected - 1;
    //int tab = (wnd.interf_.fields_[0].buttons_[0]->status_ == 3) ? 0 : 1;

    objectSelected = 0;

    if (!rt.objects_.empty()) {
        rt.objects_.erase(rt.objects_.begin() + id);
        rt.object_count_--;
    }

    createFields();

    //(tab == 0) ? Edit() : Objects();
}

void SaveSettings() {
    prop.saveProperties();
}

void SelectObj() {
    POINT pos = mousePos();
    pos.y -= 30;

    objectSelected = int ((pos.y + wnd.interf_.fields_[2].pos_.y - wnd.interf_.fields_[2].buttons_[0]->wndPos_.y) / 50) + 1; //??? временно. надо сделать класс кнопки, в которой хранится id объекта //очень классный костыль(нет)

    for (int i = 0; i < rt.object_count_; ++i) rt.objects_[i]->status_ = false;
    rt.objects_[objectSelected - 1]->status_ = true;

    wnd.bindButtonsToObject(rt.objects_[objectSelected - 1]);
}

void Save() {
    OPENFILENAMEA ofn = {};
    char fn[MAX_PATH] = ""; 

    ofn.lStructSize     = sizeof(ofn);
    ofn.hwndOwner       = NULL;
    ofn.lpstrFile       = fn;
    ofn.nMaxFile        = MAX_PATH;
    ofn.lpstrFilter     = "RTRTRT\0*.RT*\0\0";
    ofn.nFilterIndex    = 1;
    ofn.lpstrFileTitle  = NULL;
    ofn.nMaxFileTitle   = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags           = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
    ofn.lpstrDefExt     = "rt";
    ofn.FlagsEx         = 0;

    if (!GetSaveFileNameA(&ofn)) return;

    std::ofstream file(fn);

    if (!file) {
        printf("File does not exist!\n"); 

        return;
    }

    for (int obj = 0; obj < rt.object_count_; ++obj) {
        Object* object = rt.objects_[obj];

        if (object->type > 0) file << object->type << " " 
            << object->mat_.reflection << " " << object->mat_.n       << " " << object->mat_.transparency << " " << object->mat_.roughness << " "
            << object->size_.x_        << " " << object->size_.y_     << " " << object->size_.z_          << " "
            << object->center_.x_      << " " << object->center_.y_   << " " << object->center_.z_        << " "
            << object->color_.x_       << " " << object->color_.y_    << " " << object->color_.z_         << " "
            << object->rotation_.x_    << " " << object->rotation_.y_ << " " << object->rotation_.z_      << std::endl;

        else file << object->type << " " 
            << object->mat_.reflection << " " << object->mat_.n       << " " << object->mat_.transparency << " " << object->mat_.roughness << " "
            << object->center_.x_      << " " << object->center_.y_   << " " << object->center_.z_        << " "
            << object->color_.x_       << " " << object->color_.y_    << " " << object->color_.z_         << " "
            << object->rotation_.x_    << " " << object->rotation_.y_ << " " << object->rotation_.z_      << std::endl;
    }

    file.close();
}

void Load() {
    OPENFILENAMEA ofn = {};
    char fn[MAX_PATH] = ""; 

    ofn.lStructSize     = sizeof(ofn);
    ofn.hwndOwner       = NULL;
    ofn.lpstrFile       = fn;
    ofn.nMaxFile        = MAX_PATH;
    ofn.lpstrFilter     = "RTRTRT\0*.RT*\0\0";
    ofn.nFilterIndex    = 1;
    ofn.lpstrFileTitle  = NULL;
    ofn.nMaxFileTitle   = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags           = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
    ofn.lpstrDefExt     = "rt";
    ofn.FlagsEx         = 0;

    if (!GetOpenFileNameA(&ofn)) return;

    std::string line = "", word = "";
    std::ifstream file(fn);

    if (!file) {
        printf("File does not exist!\n");

        return;
    }

    else {
        rt.objects_.clear();
        rt.object_count_ = 0;
        
        objectSelected = 0;

        while(getline(file, line)) {
            std::istringstream iss(line, std::istringstream::in);
            std::vector<std::string> wordsVector;

            while (iss >> word) {
                wordsVector.push_back(word);
            }

            rt.object_count_++;

            if      (wordsVector[0] == "0") rt.objects_.push_back(new Plane  {{std::stod(wordsVector[1 ]), std::stod(wordsVector[2 ]), std::stod(wordsVector[3 ]), std::stod(wordsVector[4])}, 
                                                                              {std::stod(wordsVector[5 ]), std::stod(wordsVector[6 ]), std::stod(wordsVector[7 ])},
                                                                              {std::stod(wordsVector[8 ]), std::stod(wordsVector[9 ]), std::stod(wordsVector[10])}, 
                                                                              {std::stod(wordsVector[11]), std::stod(wordsVector[12]), std::stod(wordsVector[13])}});

            else if (wordsVector[0] == "1") rt.objects_.push_back(new Sphere {{std::stod(wordsVector[1 ]), std::stod(wordsVector[2 ]), std::stod(wordsVector[3 ]), std::stod(wordsVector[4])}, 
                                                                              {std::stod(wordsVector[5 ]), std::stod(wordsVector[6 ]), std::stod(wordsVector[7 ])},
                                                                              {std::stod(wordsVector[8 ]), std::stod(wordsVector[9 ]), std::stod(wordsVector[10])}, 
                                                                              {std::stod(wordsVector[11]), std::stod(wordsVector[12]), std::stod(wordsVector[13])}, 
                                                                              {std::stod(wordsVector[14]), std::stod(wordsVector[15]), std::stod(wordsVector[16])}});

            else if (wordsVector[0] == "2") rt.objects_.push_back(new Box    {{std::stod(wordsVector[1 ]), std::stod(wordsVector[2 ]), std::stod(wordsVector[3 ]), std::stod(wordsVector[4])}, 
                                                                              {std::stod(wordsVector[5 ]), std::stod(wordsVector[6 ]), std::stod(wordsVector[7 ])},
                                                                              {std::stod(wordsVector[8 ]), std::stod(wordsVector[9 ]), std::stod(wordsVector[10])}, 
                                                                              {std::stod(wordsVector[11]), std::stod(wordsVector[12]), std::stod(wordsVector[13])}, 
                                                                              {std::stod(wordsVector[14]), std::stod(wordsVector[15]), std::stod(wordsVector[16])}});

        }

        createFields();
    }

    file.close();
}

void Screenshot() {
    HDC save = txCreateCompatibleDC(wnd.width_, wnd.height_);
    //StretchBlt

    if (copyFromWnd(save, 0, 0, wnd.width_, wnd.height_)) {
        std::string PATH = getExeDir() + "\\screenshots\\" + getTime() + ".jpg";

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