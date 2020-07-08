#include "common.h"

#include <sstream>
#include <iostream>
#include <filesystem>

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

std::vector<std::string> parseWhere(std::string whereString, char delim) {
    std::vector<std::string> where;

    std::stringstream ss(whereString);
    std::string item;

    // get the key
    std::getline(ss, item, delim);
    where.push_back(item);

    // the delimiter will the the operator
    where.push_back(std::string(1, delim));

    // get the value
    std::getline(ss, item, delim);
    where.push_back(item);

    return where;
}

std::vector<std::string> listFilesInDirectory(std::string directory){
    std::vector<std::string> files;

    for (const auto & entry : std::filesystem::directory_iterator(directory)){
        files.push_back(entry.path());
    }

    return files;
}

std::string format(std::string str, int colSize){
    if (str.length() > colSize)
        return str;
    
    int numSpaces = colSize - str.length();
    for(int i=0; i<numSpaces; i++)
        str.append(" ");
    
    return str;
}