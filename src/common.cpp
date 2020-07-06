#include "common.h"

#include <sstream>

std::string trimEdges(std::string str) {
    bool doneFront = false, doneBack = false;

    for(int i=0; i<str.size(); i++){
        if (!doneFront && str.at(0) == ' '){
            str.erase(0, 1);
        } else {
            doneFront = true;
        }
        
        if (!doneBack && str.at(str.size()-1) == ' ') {
            str.erase(str.size() -1, 1);
        } else {
            doneBack = true;
        }

        if (doneBack && doneFront) {
            return str;
        }
    }
    return str;
}

std::vector<std::shared_ptr<std::string>> splitSharedPtr(std::string dataLine, char delim) {
    std::vector<std::shared_ptr<std::string>> data;

    std::stringstream ss(dataLine);
    std::string item;
    while(std::getline(ss, item, delim)){
        data.push_back(std::make_shared<std::string>(item));
    }

    return data;
}

std::vector<std::string> splitRValue(std::string dataLine, char delim) {
    std::vector<std::string> data;

    std::stringstream ss(dataLine);
    std::string item;
    while(std::getline(ss, item, delim)){
        data.push_back(item);
    }

    return data;
}