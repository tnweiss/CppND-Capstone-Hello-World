#include <iostream>
#include <string>
#include <cstring>
#include <chrono>
#include "sources.h"
#include "query.h"
#include "common.h"
#include "engine.h"

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    // pretty print
    std::cout << "\n----------File Query Engine----------\n\n";

    // if we have an odd number of arguments something went wrong
    if(argc % 2 == 0){
        std::cout << std::endl << "Invalid number of arguments: " << argc << std::endl;
        return 2;
    }

    // look for the config file argument in the list of arguments
    std::string configFile = "", dataDir = "";
    int numThreads = 1;
    for (int i=1; i<argc - 1; i++){
        if (strcmp(argv[i],"--config") == 0){
            configFile = argv[i+1];
            i++;
        } else if (strcmp(argv[i],"--data") == 0){
            dataDir = argv[i+1];
            i++;
        } else if (strcmp(argv[i],"--threads") == 0){
            numThreads = std::stoi(argv[i+1]);
        }
    }

    //print the config file name for debugging and then load the sources config
    std::cout << "Loading config file from: " << configFile << std::endl;
    Sources _sources(configFile);

    std::cout << "\nLoading data from: " << dataDir << std::endl;
    listFilesInDirectory(dataDir);

    std::cout << "\nUsing " << numThreads << " threads" << std::endl;

    // load the query object and print it out in a pretty format
    Query q(argc, argv, _sources);
    std::cout << "\nQUERY:\n" << q;

    Engine engine(&q, listFilesInDirectory(dataDir));
    engine.start(numThreads);
    engine.blockForResults();
    std::cout << "\nResults:" << std::endl << engine << std::endl;

    // calculate the execution time
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "\nFound " << engine.resultsSize() << " results" << std::endl;
    std::cout << "Execution Time: " << duration << " milliseconds" << std::endl << std::endl;

    return 0;
}