#include "dataframe.h"

#include <sstream>
#include <vector>

#include "common.h"

Dataframe::Dataframe(std::string dataLine){
    _data = splitSharedPtr(dataLine, '\t');
    _id = new std::string(gen_random(10));
}

Dataframe::Dataframe(std::vector<std::shared_ptr<std::string>> data) {
    this->_data  = data;
    _id = new std::string(gen_random(10));
}

Dataframe::~Dataframe(){
    delete _id;
}

std::shared_ptr<std::string> Dataframe::get(int index) {
    return _data.at(index);
}


Dataframe::Dataframe(const Dataframe& dataframe){
    _data = dataframe._data;
    _id = new std::string(dataframe._id->data());
} // copy constructor

Dataframe Dataframe::operator=(const Dataframe& dataframe){
    if( this == &dataframe) {
        return *this;
    }

    _data = dataframe._data;
    _id = new std::string(dataframe._id->data());

    return *this;
} //copy assignment

Dataframe::Dataframe(Dataframe &&dataframe){
    _data = dataframe._data;
    _id = dataframe._id;

    dataframe._data.clear();
    dataframe._id = nullptr;
} // move

Dataframe &Dataframe::operator=(Dataframe&& dataframe){
    _data = dataframe._data;
    _id = dataframe._id;

    dataframe._data.clear();
    dataframe._id = nullptr;

    return *this;
} // move assignment
