#include "engine.h"

#include <thread>
#include <iostream>
#include <fstream>
#include "query.h"

Engine::Engine(Query *q, std::vector<std::string> files){
    _query = q;
    for (auto f: files) {
        _files.push(f);
    }
}

void Engine::start(int numthreads){
    for (int i=0; i<numthreads; i++) {
        _threads.emplace_back(std::thread(&Engine::executeQuery, this));
    }
}

void Engine::addResult(Dataframe df) {

}

void Engine::blockForResults() {
    for (auto &t : _threads)
        t.join();
}

void Engine::executeQuery(){
    while(!_files.empty()){
        // get the filename
        std::string filename = _files.pop();
        std::cout << "Querying " << filename << std::endl;
        // initialize data to be used
        std::vector<Dataframe> data;
        // open the file and parse each line to a dataframe
        std::string line, key, value;
        std::ifstream filestream(filename);
        if (filestream.is_open()) {
            while (std::getline(filestream, line)) {
                data.push_back(Dataframe(line));
            }
        }
        std::cout << "Loaded " << data.size() << " dataframes" << std::endl;
        // pass each line to the query to get the dataframe matches
        for (Dataframe df: data) {
            ResultFrame result = _query->query(df);
            if (result.foundMatch()) {
                _results.push(result);
            }
        }
        // add the data to the vector
        std::cout << "Found " << _results.size() << " matches" << std::endl;
    }


}
