#include "query.h"
#include <sstream>
#include <cstring>
#include <iostream>
#include <vector>

#include "common.h"

Query::Query(int argc, char *argv[], Sources& sources){
    // parse arguments and look for -s -f and -w 
    for (int i=1; i<argc - 1; i++){
        // -s is short for SELECT, should come in the form of a comma seperated list
        if (strcmp(argv[i],"-s") == 0) {
            _select = splitRValue(argv[i+1], ',');
        // -f is short for FROM, should come in the form of a string
        } else if (strcmp(argv[i], "-f") == 0) {
            _from = sources.GetSource(argv[i+1]);
        // -w is short for WHERE, should look like KEY=VALUE
        } else if (strcmp(argv[i], "-w") == 0) {
            std::vector<std::string> whereTmp = parseWhere(argv[i+1], '=');
            _where[2] = whereTmp.at(2);
            _where[1] = whereTmp.at(1);
            _where[0] = whereTmp.at(0);
        }
    }
}

ResultFrame Query::query(Dataframe dataframe){
    // if we find the equal operation then evaluate
    if (strcmp(_where[1].c_str(), "=") == 0) {
        // get the index of the key in the dataframe
        int index = _from->GetKeyIndex(_where[0]);
        // if index is -1 then throw an error
        if (index == -1) {
            std::cout << "Key " << _where[0] << " not found" << std::endl;
            exit(1);
        }
        // compare the datafram value to the value in the query
        if( strcmp(dataframe.get(index)->c_str(),_where[2].c_str()) == 0){
            // if there is a match then get the selected data 
            std::vector<std::shared_ptr<std::string>> selectData;
            // for each data set add a pointer to the data to the data subset
            for (std::string str : _select){
                int selectDataIndex = _from->GetKeyIndex(str);
                selectData.push_back(dataframe.get(selectDataIndex)); 
            }
            // return the new subset of data
            return ResultFrame(selectData, true);
        }
    // if no operator matches are found throw an error
    } else {
        std::cout << "ERROR: Operation " << _where[1] << " not supported" << std::endl;
        exit(1);
    }
    // return null pointer
    return ResultFrame("", false);
}
