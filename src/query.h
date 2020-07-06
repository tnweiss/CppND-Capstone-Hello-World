#ifndef QUERY_H
#define QUERY_H

#include <string>
#include <vector>
#include <iostream>

#include "sources.h"
#include "dataframe.h"

class Query {
    public:
        Query(int argc, char*[], Sources&);
        std::shared_ptr<Dataframe> query(Dataframe dataframe, std::shared_ptr<Dataframe>);

        friend std::ostream &operator<<(std::ostream & Str, const Query& q){
            Str << "SELECT ";
            for (std::string s: q._select){
                Str << s << ", ";
            }
            Str << std::endl;

            Str << "FROM " << q._from->GetSourceName() << std::endl;
            
            Str << "WHERE " << q._where[0] << " " << q._where[1] << " " << q._where[2] << std::endl;

            return Str;
        }

    private:
        std::vector<std::string> _select;
        Source *_from;
        std::string _where[3];
};

#endif