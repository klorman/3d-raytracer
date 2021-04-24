#pragma once

#include "Vector.hpp"

#include <fstream>
#include <vector>

class Vector;

struct Properties {
    double UPSCALING;
    Vector BACKGROUNDCOLOR;

    Properties();

    void loadProperties();
    void saveProperties();
};