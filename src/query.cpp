#include "query.h"
#include <sstream>
#include <cstring>
#include <iostream>

#include "common.h"

Query::Query(int argc, char *argv[], Sources& sources){
    std::cout << "hello 1" << std::endl;
    for (int i=1; i<argc - 1; i++){
        if (strcmp(argv[i],"-s") == 0) {
            std::cout << "hello 2" << std::endl;
            _select = splitRValue(argv[i+1], ',');
        } else if (strcmp(argv[i], "-f") == 0) {
            std::cout << "hello 3 " << argv[i+1] << std::endl;
            _from = sources.GetSource(argv[i+1]);
            std::cout << "why " << std::endl;
        } else if (strcmp(argv[i], "-w") == 0) {
            std::cout << argv[i+1] << std::endl;
        }
    }
}

std::shared_ptr<Dataframe> &Query::query(Dataframe dataframe){
    std::shared_ptr<Dataframe> rdf = nullptr;

    if (strcmp(_where[1].c_str(), "=")) {
        int index = _from->GetKeyIndex(_where[0]);
        if( strcmp(dataframe.get(index)->c_str(),_where[2].c_str()) == 0){
            std::vector<std::shared_ptr<std::string>> selectData;
            for (std::string str : _select){
                int selectDataIndex = _from->GetKeyIndex(str);
                //selectData.push_back(std::make_shared<std::string>(dataframe.get(index))); 
            }
            rdf = std::make_shared<Dataframe>(selectData);
        }
    }else {
        std::cout << "ERROR: Operation " << _where[1] << " not supported" << std::endl;
    }
    return rdf;
}
