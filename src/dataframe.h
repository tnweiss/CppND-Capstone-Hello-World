#ifndef DATAFRAME_H
#define DATAFRAME_H

#include <vector>
#include <string>
#include <memory>

class Dataframe {
    public:
        Dataframe(std::string);
        Dataframe(std::vector<std::shared_ptr<std::string>>);
        ~Dataframe();
        Dataframe(const Dataframe&); // copy constructor
        Dataframe operator=(const Dataframe&); //copy assignment
        Dataframe(Dataframe &&); // move
        Dataframe &operator=(Dataframe&&); // move assignment

        std::ostream &operator<<(std::ostream & Str); // used to print object to console
        std::shared_ptr<std::string> get(int);

    private:
        std::vector<std::shared_ptr<std::string>> _data;
};

#endif