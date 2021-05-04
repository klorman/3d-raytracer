#pragma once

#include "Vector.hpp"

#include <fstream>
#include <vector>
#include <windows.h>
#include <string>
#include <iostream>

class Vector;

struct Properties {
    double UPSCALING;
    Vector BACKGROUNDCOLOR;
    double MAXGEN;
    double FOV;
    double FOCUS;
    double BLURRADIUS;

    Properties();

    void loadProperties();
    void saveProperties();
};

extern Properties prop;

std::string getExeDir();