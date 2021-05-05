#include "Properties.hpp"

Properties prop;

Properties::Properties() :
    INTERFACECOLOR  ({ 70, 70, 70 }),
    UPSCALING       (1),
    BACKGROUNDCOLOR ({0.2, 0.2, 0.8}),
    MAXGEN          (8),
    FOV             (90),
    FOCUS           (10),
    BLURRADIUS      (100)
{
    loadProperties();
}

void Properties::loadProperties() {
    std::string line = "", word = "";
    std::ifstream file(getExeDir() + "\\properties.txt");

    if (!file) {
        printf("properties.txt does not exist!");

        return;
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
        else if (wordsVector[0] == "MAXGEN")          MAXGEN          =  std::stod(wordsVector[1]);
        else if (wordsVector[0] == "FOV")             FOV             =  std::stod(wordsVector[1]);
        else if (wordsVector[0] == "FOCAL")           FOCUS           =  std::stod(wordsVector[1]);
        else if (wordsVector[0] == "BLURRADIUS")      BLURRADIUS      =  std::stod(wordsVector[1]);
        
    }

    file.close();
}

void Properties::saveProperties() {
    std::ofstream file(getExeDir() + "\\properties.txt");

    if (!file) {
        printf("properties.txt does not exist!");

        return;
    }

    file << "UPSCALING       " << UPSCALING << std::endl;
    file << "BACKGROUNDCOLOR " << BACKGROUNDCOLOR.x_ << " " << BACKGROUNDCOLOR.y_ << " " << BACKGROUNDCOLOR.z_ << std::endl;
    file << "MAXGEN          " << MAXGEN << std::endl;
    file << "FOV             " << FOV << std::endl;
    file << "FOCAL           " << FOCUS << std::endl;
    file << "BLURRADIUS      " << BLURRADIUS << std::endl;

    file.close();
}

std::string getExeDir() {
    char buffer[MAX_PATH];
    GetModuleFileNameA( NULL, buffer, MAX_PATH );
    std::string f = buffer;

    return f.substr(0, f.find_last_of("\\/"));
}