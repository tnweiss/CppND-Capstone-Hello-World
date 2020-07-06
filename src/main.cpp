#include <iostream>
#include <string>
#include <cstring>
#include "sources.h"
#include "query.h"

int main(int argc, char *argv[]) {

    if(argc % 2 == 0){
        std::cout << "Invalid number of arguments: " << argc << std::endl;
        return 2;
    }

    std::string configFile = "";

    for (int i=1; i<argc - 1; i++){
        if (strcmp(argv[i],"--config") == 0){
            configFile = argv[i+1];
            i++;
        } else {
            std::cout << "Error, Unknown argument '" << argv[i] << "'" << std::endl;
        }
    }

    std::cout << "Using config file: " << configFile << std::endl;

    Sources _sources(configFile);
    std::cout << "check" << std::endl;
    Query q(argc, argv, _sources);
    std::cout << q;

    std::cout << "Source key index test: " << _sources.GetSourceKeyIndex("testSource", "testKey2") << std::endl;

    return 0;
}