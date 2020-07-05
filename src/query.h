#ifndef QUERY_H
#define QUERY_H

#include <string>
#include <vector>

#include "sources.h"
#include "dataframe.h"

class Query {
    public:
        Query(char*[], Sources&);
        Dataframe &query(Dataframe dataframe);

        std::ostream &operator<<(std::ostream & Str); // used to print object to console

    private:
        std::vector<std::string> _select;
        std::vector<int> _selectIndecies;
        std::string _from;
        std::string _where[3];
};

#endif