#pragma once

#include "Vector.hpp"

#include <fstream>
#include <vector>
#include <windows.h>
#include <string>

class Vector;

struct Properties {
    double UPSCALING;
    Vector BACKGROUNDCOLOR;

    Properties();

    void loadProperties();
    void saveProperties();
};

std::string getExeDir();