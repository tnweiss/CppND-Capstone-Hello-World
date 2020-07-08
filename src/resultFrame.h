#ifndef RESULTFRAME_H
#define RESULTFRAME_H

#include "dataframe.h"

class ResultFrame: public Dataframe{
    public:
        ResultFrame(std::vector<std::shared_ptr<std::string>> df, bool match): Dataframe(df), _match(match) {  }
        ResultFrame(std::string df, bool match): Dataframe(df) {
            _match = match;
        }
        bool foundMatch() {
            return _match;
        }
        std::string toString(){return "ResultSet: " + *_id;}
    
    private:
        bool _match;

};

#endif