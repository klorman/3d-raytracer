#include "Properties.hpp"

Properties::Properties() :
    UPSCALING       (0),
    BACKGROUNDCOLOR (NULLVEC)
{
    loadProperties();
}

void Properties::loadProperties() {
    std::string line = "", word = "";
    std::ifstream file("properties.txt");

    if (!file) std::cerr << "Файла properties.txt не существует!";

    while(getline(file, line)) {
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

void Properties::saveProperties() { // запись в файл

}