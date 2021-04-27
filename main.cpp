#include "TXLib.h"
#include "Window.hpp"
#include "Raytracer.hpp"
#include "Camera.hpp"
#include "Properties.hpp"

#include <ctime>

#define LEN(arr) sizeof(arr) / sizeof(arr[0])

std::string getTime();

void Edit();
void Objects();
void Settings();
void Create();
void Delete();
void SaveSettings();

void Save();
void Load();
void Screenshot();
void Exit();

Properties prop;
Window wnd(800, 600, 50, 300, &prop);
Raytracer rt;

int objectSelected = 0;

void start();
void createFields();

void start() {
    std::vector<Object*> objects;
    objects.push_back(new Sphere {{ 0.0, 1.5, 0.9, 1.0  },     50      , { 300, 400, 60 }, { 1.0, 1.0, 1.0 }                            }); //прозрачный
    objects.push_back(new Sphere {{ 0.9, 1.0, 0.0, 1.0  },     50      , { 560, 400, 80 }, { 1.0, 1.0, 1.0 }                            }); //гладкий
    objects.push_back(new Sphere {{ 0.9, 1.0, 0.0, 1.0  }, {30, 30, 60}, { 600, 385, 10 }, { 1.0, 0.0, 0.0 }                            }); //гладкий
    objects.push_back(new Sphere {{ 0.9, 1.0, 0.0, 0.0  },     50      , { 400, 400, 100}, { 1.0, 1.0, 1.0 }                            }); //матовый
    objects.push_back(new Box    {{ 0.9, 1.0, 0.0, 1.0  }, {50, 20, 50}, {   0, 400, 200}, { 0.3, 0.3, 1.0 }, (Vector { 1, 1, 1}).norm()}); //гладкий
    objects.push_back(new Plane  {{ 0.9, 1.0, 0.0, 0.1  }              , { 0  , 450, 0  }, { 1.0, 1.0, 0.0 }, { 0,-1, 0}                });
    objects.push_back(new Sphere {{ 0.0, 1.0,-1.0, 0.0  },     200     , { 300, 200,-200}, { 0.9, 0.9, 0.9 }                            });  //источник

    rt.object_count_ = LEN(objects);
    rt.objects_      = objects;
    rt.prop_         = &prop;

    Camera cam = {100, {600 ,385, -100}, {0, 0, 1}, {0, 0, 0}};
    
    bool is_moved = false;
    int  frames = 0;

    wnd.interf_.draw(wnd);

    while (!wnd.should_close_) { 
        if (!isForeground()) continue;

        is_moved       |= cam.move(wnd);
        int selected    = wnd.selectObject(rt, cam);

        if (selected) objectSelected = selected - 1;
        if (wnd.interf_.fields_[0].buttons_[0]->status_ == 3 && selected) {
            if (objectSelected) {
                wnd.interf_.fields_[1].visible_ = true; 
                wnd.interf_.fields_[4].visible_ = false;
            }

            else {
                wnd.interf_.fields_[1].visible_ = false;
                wnd.interf_.fields_[4].visible_ = true;
            }

            wnd.interf_.draw(wnd);
        }

        is_moved ? frames = 0, is_moved = false : ++frames;

        wnd.update(rt, cam, frames);
    }
}

void createFields() {
    wnd.interf_.addField(1, {wnd.width_, 0 }, {wnd.interf_.right_size_, wnd.height_      }); //menu
    wnd.interf_.addField(0, {wnd.width_, 30}, {wnd.interf_.right_size_, wnd.height_ - 110}); //edit
    wnd.interf_.addField(0, {wnd.width_, 30}, {wnd.interf_.right_size_, wnd.height_ - 110}); //objects
    wnd.interf_.addField(0, {wnd.width_, 30}, {wnd.interf_.right_size_, wnd.height_ - 110}); //settings
    wnd.interf_.addField(1, {wnd.width_, 30}, {wnd.interf_.right_size_, wnd.height_ - 110}); //create


    //AbstractButton* menuButtons[] = {
    wnd.interf_.fields_[0].addButton(new BasicButton{{0                                     , 0          }, {LONG (wnd.interf_.right_size_ / 3), 30}, EVEC * 70, EVEC * 255, "Edit",       Edit});
    wnd.interf_.fields_[0].addButton(new BasicButton{{LONG (wnd.interf_.right_size_ / 3)    , 0          }, {LONG (wnd.interf_.right_size_ / 3), 30}, EVEC * 70, EVEC * 255, "Objects",    Objects});
    wnd.interf_.fields_[0].addButton(new BasicButton{{LONG (wnd.interf_.right_size_ / 3) * 2, 0          }, {LONG (wnd.interf_.right_size_ / 3), 30}, EVEC * 70, EVEC * 255, "Settings",   Settings});
    wnd.interf_.fields_[0].addButton(new BasicButton{{0                                     , wnd.height_}, {LONG (wnd.interf_.right_size_ / 4), 50}, EVEC * 70, EVEC * 255, "Save",       Save});
    wnd.interf_.fields_[0].addButton(new BasicButton{{LONG (wnd.interf_.right_size_ / 4)    , wnd.height_}, {LONG (wnd.interf_.right_size_ / 4), 50}, EVEC * 70, EVEC * 255, "Load",       Load});
    wnd.interf_.fields_[0].addButton(new BasicButton{{LONG (wnd.interf_.right_size_ / 4) * 2, wnd.height_}, {LONG (wnd.interf_.right_size_ / 4), 50}, EVEC * 70, EVEC * 255, "Screenshot", Screenshot});
    wnd.interf_.fields_[0].addButton(new BasicButton{{LONG (wnd.interf_.right_size_ / 4) * 3, wnd.height_}, {LONG (wnd.interf_.right_size_ / 4), 50}, EVEC * 70, EVEC * 255, "Exit",       Exit});

    //AbstractButton* editButtons[] = {
    wnd.interf_.fields_[1].addButton(new TextButton {nullptr, posX, {LONG (wnd.interf_.right_size_ / 3), 60 }, {LONG (wnd.interf_.right_size_ / 3), 30}, EVEC * 90, EVEC * 255});
    wnd.interf_.fields_[1].addButton(new TextButton {nullptr, posY, {LONG (wnd.interf_.right_size_ / 3), 90 }, {LONG (wnd.interf_.right_size_ / 3), 30}, EVEC * 90, EVEC * 255});
    wnd.interf_.fields_[1].addButton(new TextButton {nullptr, posZ, {LONG (wnd.interf_.right_size_ / 3), 120}, {LONG (wnd.interf_.right_size_ / 3), 30}, EVEC * 90, EVEC * 255});
    wnd.interf_.fields_[1].addButton(new TextButton {nullptr, rotX, {LONG (wnd.interf_.right_size_ / 3), 180}, {LONG (wnd.interf_.right_size_ / 3), 30}, EVEC * 90, EVEC * 255});
    wnd.interf_.fields_[1].addButton(new TextButton {nullptr, rotY, {LONG (wnd.interf_.right_size_ / 3), 210}, {LONG (wnd.interf_.right_size_ / 3), 30}, EVEC * 90, EVEC * 255});
    wnd.interf_.fields_[1].addButton(new TextButton {nullptr, rotZ, {LONG (wnd.interf_.right_size_ / 3), 240}, {LONG (wnd.interf_.right_size_ / 3), 30}, EVEC * 90, EVEC * 255});
    wnd.interf_.fields_[1].addButton(new TextButton {nullptr, szX , {LONG (wnd.interf_.right_size_ / 3), 300}, {LONG (wnd.interf_.right_size_ / 3), 30}, EVEC * 90, EVEC * 255, 1});
    wnd.interf_.fields_[1].addButton(new TextButton {nullptr, szY , {LONG (wnd.interf_.right_size_ / 3), 330}, {LONG (wnd.interf_.right_size_ / 3), 30}, EVEC * 90, EVEC * 255, 1});
    wnd.interf_.fields_[1].addButton(new TextButton {nullptr, szZ , {LONG (wnd.interf_.right_size_ / 3), 360}, {LONG (wnd.interf_.right_size_ / 3), 30}, EVEC * 90, EVEC * 255, 1});
    wnd.interf_.fields_[1].addButton(new TextButton {nullptr, colX, {LONG (wnd.interf_.right_size_ / 3), 420}, {LONG (wnd.interf_.right_size_ / 3), 30}, EVEC * 90, EVEC * 255, 0, 255, 255});
    wnd.interf_.fields_[1].addButton(new TextButton {nullptr, colY, {LONG (wnd.interf_.right_size_ / 3), 450}, {LONG (wnd.interf_.right_size_ / 3), 30}, EVEC * 90, EVEC * 255, 0, 255, 255});
    wnd.interf_.fields_[1].addButton(new TextButton {nullptr, colZ, {LONG (wnd.interf_.right_size_ / 3), 480}, {LONG (wnd.interf_.right_size_ / 3), 30}, EVEC * 90, EVEC * 255, 0, 255, 255});
        
    wnd.interf_.fields_[1].addButton(new BasicButton{{0, 0               }, {wnd.interf_.right_size_, 30}, EVEC * 70, EVEC * 255, "Create", Create});
    wnd.interf_.fields_[1].addButton(new BasicButton{{0, wnd.height_ - 60}, {wnd.interf_.right_size_, 30}, EVEC * 70, EVEC * 255, "Delete", Delete});

    //AbstractButton* settingsButtons[] = {
    wnd.interf_.fields_[3].addButton(new TextButton {&wnd.prop_->UPSCALING,          -1, {LONG (wnd.interf_.right_size_ / 3 * 2), 0  }, {LONG (wnd.interf_.right_size_ / 3), 30}, EVEC * 90, EVEC * 255, 1, 16});
    wnd.interf_.fields_[3].addButton(new TextButton {&wnd.prop_->BACKGROUNDCOLOR.x_, -1, {LONG (wnd.interf_.right_size_ / 3 * 2), 30 }, {LONG (wnd.interf_.right_size_ / 3), 30}, EVEC * 90, EVEC * 255, 0, 255, 255});
    wnd.interf_.fields_[3].addButton(new TextButton {&wnd.prop_->BACKGROUNDCOLOR.y_, -1, {LONG (wnd.interf_.right_size_ / 3 * 2), 60 }, {LONG (wnd.interf_.right_size_ / 3), 30}, EVEC * 90, EVEC * 255, 0, 255, 255});
    wnd.interf_.fields_[3].addButton(new TextButton {&wnd.prop_->BACKGROUNDCOLOR.z_, -1, {LONG (wnd.interf_.right_size_ / 3 * 2), 90 }, {LONG (wnd.interf_.right_size_ / 3), 30}, EVEC * 90, EVEC * 255, 0, 255, 255});

    wnd.interf_.fields_[3].addButton(new BasicButton{{0, wnd.height_ - 60}, {wnd.interf_.right_size_, 30}, EVEC * 70, EVEC * 255, "Save settings", SaveSettings});

    //AbstractButton* createButtons[] = {   
    wnd.interf_.fields_[4].addButton(new BasicButton{{0, 0}, {wnd.interf_.right_size_, 30}, EVEC * 70, EVEC * 255, "Create", Create});

    //Textbox editTextBoxes[] = {
    wnd.interf_.fields_[1].addTextbox({{LONG (wnd.interf_.right_size_ / 3),      30 }, {LONG (wnd.interf_.right_size_ / 3), 30}, "Coords"});
    wnd.interf_.fields_[1].addTextbox({{LONG (wnd.interf_.right_size_ / 3 - 30), 60 }, {30, 30}, "X:"});
    wnd.interf_.fields_[1].addTextbox({{LONG (wnd.interf_.right_size_ / 3 - 30), 90 }, {30, 30}, "Y:"});
    wnd.interf_.fields_[1].addTextbox({{LONG (wnd.interf_.right_size_ / 3 - 30), 120}, {30, 30}, "Z:"});
    wnd.interf_.fields_[1].addTextbox({{LONG (wnd.interf_.right_size_ / 3),      150}, {LONG (wnd.interf_.right_size_ / 3), 30}, "Rotation"});
    wnd.interf_.fields_[1].addTextbox({{LONG (wnd.interf_.right_size_ / 3 - 30), 180}, {30, 30}, "X:"});
    wnd.interf_.fields_[1].addTextbox({{LONG (wnd.interf_.right_size_ / 3 - 30), 210}, {30, 30}, "Y:"});
    wnd.interf_.fields_[1].addTextbox({{LONG (wnd.interf_.right_size_ / 3 - 30), 240}, {30, 30}, "Z:"});
    wnd.interf_.fields_[1].addTextbox({{LONG (wnd.interf_.right_size_ / 3),      270}, {LONG (wnd.interf_.right_size_ / 3), 30}, "Size"});
    wnd.interf_.fields_[1].addTextbox({{LONG (wnd.interf_.right_size_ / 3 - 30), 300}, {30, 30}, "X:"});
    wnd.interf_.fields_[1].addTextbox({{LONG (wnd.interf_.right_size_ / 3 - 30), 330}, {30, 30}, "Y:"});
    wnd.interf_.fields_[1].addTextbox({{LONG (wnd.interf_.right_size_ / 3 - 30), 360}, {30, 30}, "Z:"});
    wnd.interf_.fields_[1].addTextbox({{LONG (wnd.interf_.right_size_ / 3),      390}, {LONG (wnd.interf_.right_size_ / 3), 30}, "Color"});
    wnd.interf_.fields_[1].addTextbox({{LONG (wnd.interf_.right_size_ / 3 - 30), 420}, {30, 30}, "R:"});
    wnd.interf_.fields_[1].addTextbox({{LONG (wnd.interf_.right_size_ / 3 - 30), 450}, {30, 30}, "G:"});
    wnd.interf_.fields_[1].addTextbox({{LONG (wnd.interf_.right_size_ / 3 - 30), 480}, {30, 30}, "B:"});

    //Textbox settingsTextBoxes[] = {
    wnd.interf_.fields_[3].addTextbox({{0, 0 }, {LONG (wnd.interf_.right_size_ / 3 * 2), 30}, "UPSCALING"       , wnd.interf_.BACKGROUND});
    wnd.interf_.fields_[3].addTextbox({{0, 30}, {LONG (wnd.interf_.right_size_ / 3 * 2), 90}, "BACKGROUND COLOR", wnd.interf_.BACKGROUND});

    //Textbox createTextBoxes[] = {
    wnd.interf_.fields_[4].addTextbox({{0, wnd.height_ >> 1}, {wnd.interf_.right_size_, 60}, "Create or select an object", -EVEC, EVEC * 150});                                                                                                                                                       
}

int main() {
    createFields();

    start();
}

void Edit() {
    if (objectSelected) {
        wnd.interf_.fields_[1].visible_ = true;
        wnd.interf_.fields_[4].visible_ = false;
    }

    else {
        wnd.interf_.fields_[1].visible_ = false;
        wnd.interf_.fields_[4].visible_ = true;
    }

    wnd.interf_.fields_[2].visible_ = false;
    wnd.interf_.fields_[3].visible_ = false;

    wnd.interf_.fields_[0].buttons_[0]->status_ = 3;
    wnd.interf_.fields_[0].buttons_[1]->status_ = 0;
    wnd.interf_.fields_[0].buttons_[2]->status_ = 0;

    wnd.interf_.draw(wnd);
}

void Objects() {
    wnd.interf_.fields_[1].visible_ = false;
    wnd.interf_.fields_[2].visible_ = !wnd.interf_.fields_[2].visible_;
    wnd.interf_.fields_[3].visible_ = false;
    wnd.interf_.fields_[4].visible_ = false;

    wnd.interf_.fields_[0].buttons_[0]->status_ = 0;
    wnd.interf_.fields_[0].buttons_[1]->status_ = 3;
    wnd.interf_.fields_[0].buttons_[2]->status_ = 0;

    wnd.interf_.draw(wnd);
}

void Settings() {
    wnd.interf_.fields_[1].visible_ = false;
    wnd.interf_.fields_[2].visible_ = false;
    wnd.interf_.fields_[3].visible_ = !wnd.interf_.fields_[3].visible_;
    wnd.interf_.fields_[4].visible_ = false;

    wnd.interf_.fields_[0].buttons_[0]->status_ = 0;
    wnd.interf_.fields_[0].buttons_[1]->status_ = 0;
    wnd.interf_.fields_[0].buttons_[2]->status_ = 3;

    wnd.interf_.draw(wnd);
}

void Create() {
    rt.objects_.push_back(new Sphere {{ 0.9, 1.0, 0.0, 1.0  }, 50, { 0, 0, 0 }, { 1.0, 1.0, 1.0 }});
    rt.object_count_++;

    wnd.bindButtonsToObject(rt.objects_.back());
    objectSelected = (int) rt.objects_.size();
    
    Edit();
    //wnd.interf_.fields_[1].visible_ = true;
    //wnd.interf_.fields_[4].visible_ = false;
    //wnd.interf_.draw(wnd);
}

void Delete() {
    int id = objectSelected - 1;

    objectSelected = 0;
    wnd.interf_.fields_[1].visible_ = false;
    wnd.interf_.fields_[4].visible_ = true;
    wnd.interf_.draw(wnd);

    if (!rt.objects_.empty()) {
        rt.objects_.erase(rt.objects_.begin() + id);
        rt.object_count_--;
    }
}

void SaveSettings() {
    prop.saveProperties();
}

void Save() {
    std::ofstream file(getExeDir() + "\\save.rt");

    if (!file) {
        std::cerr << "save.txt does not exist!";

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
//    char fn[MAX_PATH]; 
//    OPENFILENAMEA ofn;
//
//    fn[0] = '\0';
//    ZeroMemory(&ofn, sizeof(ofn));
//    ofn.lStructSize = sizeof(OPENFILENAMEA);
//    ofn.hwndOwner = NULL;
//    ofn.lpstrFilter = "Вс фйл\0*.*\0\0";
//    ofn.lpstrCustomFilter = NULL;
//    ofn.nFilterIndex = 1;
//    ofn.lpstrFile = fn;
//    ofn.nMaxFile = MAX_PATH;
//    ofn.lpstrFileTitle = NULL;
//    ofn.lpstrInitialDir = NULL;
//    ofn.lpstrTitle = NULL;
//    ofn.Flags = OFN_EXPLORER;
//    ofn.lpstrDefExt = "rt";
//    ofn.FlagsEx = 0;

    //std::cout << GetOpenFileNameA(&ofn); //help me

//    std::cout << fn;

    std::string line = "", word = "";
    std::ifstream file(getExeDir() + "\\save.rt");

    if (!file) {
        std::cerr << "properties.txt does not exist!";

        return;
    }

    else {
        rt.objects_.clear();
        rt.object_count_ = 0;
        
        objectSelected = 0;
        if (wnd.interf_.fields_[1].visible_) {
            wnd.interf_.fields_[1].visible_ = false;
            wnd.interf_.fields_[4].visible_ = true;
            wnd.interf_.draw(wnd);
        }

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
    }

    file.close();
}

void Screenshot() {
    HDC save = txCreateCompatibleDC(wnd.width_, wnd.height_);

    if (bitBlt(save, 0, 0, wnd.width_, wnd.height_)) {
        std::string PATH = getExeDir() + std::string("\\screenshots\\") + getTime() + std::string(".jpg");

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