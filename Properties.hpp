#pragma once

#include "Vector.hpp"

class Vector;

struct Properties {
    double UPSCALING;
    Vector BACKGROUNDCOLOR;

    Properties();

    void loadProperties();
    void saveProperties();
};