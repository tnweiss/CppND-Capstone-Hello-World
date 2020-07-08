#include "engine.h"

#include <thread>
#include <iostream>
#include <fstream>
#include <vector>
#include <future>
#include <chrono>
#include "query.h"
#include "common.h"

Engine::Engine(Query *q, std::vector<std::string> files){
    _query = q;
    for (auto f: files) {
        _files.push(f);
    }
}

void Engine::start(int numthreads){
    std::vector<std::thread> _threads;
    std::vector<std::future<std::string>> _futures;

    for (int i=0; i<numthreads; i++) {
        // create promise and future
        std::promise<std::string> prms = std::promise<std::string>();
        std::future<std::string> ftr = prms.get_future();

        _threads.emplace_back(std::thread(&Engine::executeQuery, this, std::move(prms)));
        _futures.emplace_back(std::move(ftr));
    }

    std::cout << std::endl << "Thread Summary:" << std::endl;
    for (int i=0; i<_threads.size(); i++) {
        std::cout << _futures.at(i).get() << std::endl;
        _threads.at(i).join();
    }
}

void Engine::executeQuery(std::promise<std::string> &&prms){
    int numEntries = 0;
    auto start = std::chrono::high_resolution_clock::now();

    while(!_files.empty()){
        // get the filename
        std::string filename = _files.pop();
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
        // pass each line to the query to get the dataframe matches
        for (Dataframe df: data) {
            ResultFrame result = _query->query(df);
            if (result.foundMatch()) {
                _results.push(result);
            }
            numEntries++;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    prms.set_value("Thread " + thread_id_string() + " parsed " + std::to_string(numEntries) + 
        " lines in " + std::to_string(duration) + " milliseconds");
}
