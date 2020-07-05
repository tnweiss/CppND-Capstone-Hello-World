#include "query.h"
#include <sstream>

Query::Query(char* argv[], Sources& sources){

}

Dataframe &Query::query(Dataframe dataframe){

}

std::ostream &Query::operator<<(std::ostream & Str){
    Str << "Select ";
    for (std::string s: _select){
        Str << s << ", ";
    }
    Str << std::endl;

    Str << "From " << _from << std::endl;
    
    Str << "Where " << _where[0] << " " << _where[1] << " " << _where[2] << std::endl;
}