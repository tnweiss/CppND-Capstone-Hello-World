#include <iostream>
#include <string>
#include <cstring>
#include "sources.h"
#include "query.h"
#include "common.h"

int main(int argc, char *argv[]) {
    // pretty print
    std::cout << "\n----------File Query Engine----------\n\n";

    // if we have an odd number of arguments something went wrong
    if(argc % 2 == 0){
        std::cout << std::endl << "Invalid number of arguments: " << argc << std::endl;
        return 2;
    }

    // look for the config file argument in the list of arguments
    std::string configFile = "", dataDir = "";
    for (int i=1; i<argc - 1; i++){
        if (strcmp(argv[i],"--config") == 0){
            configFile = argv[i+1];
            i++;
        } else if (strcmp(argv[i],"--data") == 0){
            dataDir = argv[i+1];
            i++;
        }
    }

    //print the config file name for debugging and then load the sources config
    std::cout << "Loading config file:\n" << configFile << std::endl;
    Sources _sources(configFile);

    std::cout << "\nData files in " << dataDir << ":\n" << std::endl;
    listFilesInDirectory(dataDir);

    // load the query object and print it out in a pretty format
    Query q(argc, argv, _sources);
    std::cout << "\nQUERY:\n" << q;

    // TEST!!!!
    // load data
    

    return 0;
}