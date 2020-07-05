#ifndef SOURCE_H
#define SOURCE_H

#include <vector>
#include <string>
#include <memory>

class Source {
    public:
        Source(std::string); // constructor
        ~Source(); // destructor
        Source(const Source&); // copy constructor
        Source operator=(const Source&); // copy assignment
        Source(Source &&source); // move 
        Source &operator=(Source &&source); // move assignment

        int GetKeyIndex(std::string);
        std::string GetSourceName();
        void AddKey(std::string);
    

    private:
        std::unique_ptr<std::vector<std::string>> _keys;
        std::string _sourceName;
};

#endif