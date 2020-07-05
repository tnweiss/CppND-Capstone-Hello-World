#include "common.h"

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