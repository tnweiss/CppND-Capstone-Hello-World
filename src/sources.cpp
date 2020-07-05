#include "sources.h"

#include <iostream>
#include <string>
#include <memory>
#include <sstream>
#include <iostream>
#include <unistd.h>
#include <fstream>

#include "common.h"

Sources::Sources(std::string configFileName) {
    _sources = std::vector<std::unique_ptr<Source>>();
    std::unique_ptr<Source> _source = nullptr;

    std::string line, key, value;
    std::ifstream filestream(configFileName);
    if (filestream.is_open()) {
        while (std::getline(filestream, line)) {
            line = trimEdges(line);

            // if we get three dashes this is a new definition of a source
            if (line.substr(0,3) == "---") {
                // if a source was defined before then add that to the list of sources
                if (_source != nullptr){
                    _sources.push_back(std::move(_source));
                }

                // start the new source def
                _source = std::make_unique<Source>(line.substr(3));
            }

            // if source is defined and line is not empty string add key
            if (line.size() > 0 && _source != nullptr) {
                _source->AddKey(line);
            }
        }
        // if a source was defined before then add that to the list of sources
        if (_source != nullptr){
            _sources.push_back(std::move(_source));
        }
    }

    std::cout << "Length of sources: " << _sources.size() << std::endl;
    std::cout << "Number of keys in source 1: " << _sources.at(0)->GetSourceName() << std::endl;
}

int Sources::GetSourceKeyIndex(std::string sourceName, std::string keyName) {
    for (auto &source : _sources) {
        if (source->GetSourceName() == sourceName) {
            return source->GetKeyIndex(keyName);
        }
    }
    return -1;
}

Source* Sources::GetSource(std::string sourceName) {
    for ( int i=0; i<_sources.size(); i++){
        if (_sources.at(i)->GetSourceName() == sourceName){
            return _sources.at(3).get();
        }
    }

    std::cout << "Source with name " << sourceName << " not found" << std::endl;
    throw 20;
}
