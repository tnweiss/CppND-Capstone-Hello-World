#ifndef DATAFRAME_H
#define DATAFRAME_H

#include <vector>
#include <string>
#include <memory>
#include <iostream>

class Dataframe {
    public:
        Dataframe(std::string);
        Dataframe(std::vector<std::shared_ptr<std::string>>);
        ~Dataframe();
        Dataframe(const Dataframe&); // copy constructor
        Dataframe operator=(const Dataframe&); //copy assignment
        Dataframe(Dataframe &&); // move
        Dataframe &operator=(Dataframe&&); // move assignment

        friend std::ostream &operator<<(std::ostream & Str, const Dataframe df){
            for (std::shared_ptr<std::string> d: df._data){
                Str << d.get()->data() << ", ";
            }
            Str << std::endl;
            return Str;
        }
        std::shared_ptr<std::string> get(int);

    private:
        std::vector<std::shared_ptr<std::string>> _data;
};

#endif