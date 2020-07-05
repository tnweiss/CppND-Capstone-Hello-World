#ifndef SOURCES_H
#define SOURCES_H

#include <vector>
#include <string>
#include <memory>

#include "source.h"

class Sources {
    public:
        Sources(std::string);
        Source* GetSource(std::string);
        int GetSourceKeyIndex(std::string, std::string);

    private:
        std::vector<std::unique_ptr<Source>> _sources;
};

#endif