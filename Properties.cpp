#include "Properties.hpp"

Properties::Properties() :
    UPSCALING       (0),
    BACKGROUNDCOLOR (NULLVEC)
{
    loadProperties();
}

void Properties::loadProperties() {
    std::string line = "", word = "";
    std::ifstream file(getExeDir() + "\\properties.txt");

    if (!file) {
        std::cerr << "properties.txt does not exist!"; //загрузка настроек по умолчанию

        UPSCALING = 1;
        BACKGROUNDCOLOR = {0.5, 0.5, 1.0};
    }

    else while(getline(file, line)) {
        std::istringstream iss(line, std::istringstream::in);
        std::vector<std::string> wordsVector;
        
        while (iss >> word) {
            wordsVector.push_back(word);
        }

        if      (wordsVector[0] == "UPSCALING")       UPSCALING       =  std::stod(wordsVector[1]);
        else if (wordsVector[0] == "BACKGROUNDCOLOR") BACKGROUNDCOLOR = {std::stod(wordsVector[1]), 
                                                                         std::stod(wordsVector[2]), 
                                                                         std::stod(wordsVector[3])};
    }

    file.close();
}

void Properties::saveProperties() {
    std::ofstream file(getExeDir() + "\\properties.txt");

    if (!file) {
        std::cerr << "properties.txt does not exist!";

        return;
    }

    file << "UPSCALING       " << UPSCALING << std::endl;
    file << "BACKGROUNDCOLOR " << BACKGROUNDCOLOR.x_ << " " << BACKGROUNDCOLOR.y_ << " " << BACKGROUNDCOLOR.z_ << std::endl;

    file.close();
}

std::string getExeDir() {
    char buffer[MAX_PATH];
    GetModuleFileNameA( NULL, buffer, MAX_PATH );
    std::string f = buffer;

    return f.substr(0, f.find_last_of("\\/"));
}