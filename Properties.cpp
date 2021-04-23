#include "Properties.hpp"

Properties::Properties() :
    UPSCALING       (0),
    BACKGROUNDCOLOR (NULLVEC)
{
    loadProperties();
}

void Properties::loadProperties() { //чтение из файла
    UPSCALING       = 2;
    BACKGROUNDCOLOR = { 0.5, 0.5, 1.0 };
}

void Properties::saveProperties() { // запись в файл

}