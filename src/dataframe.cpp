#include "dataframe.h"

#include <sstream>
#include <vector>

Dataframe::Dataframe(std::string dataLine){
    std::stringstream ss(dataLine);
    std::string item;
    while(std::getline(ss, item, ',')){
        _data.push_back(std::make_shared<std::string>(item));
    }
}

Dataframe::Dataframe(std::vector<std::shared_ptr<std::string>> data) {
    this->_data  = data;
}

Dataframe::~Dataframe(){

}


Dataframe::Dataframe(const Dataframe& dataframe){
    _data = dataframe._data;
} // copy constructor

Dataframe Dataframe::operator=(const Dataframe& dataframe){
    if( this == &dataframe) {
        return *this;
    }

    _data = dataframe._data;
} //copy assignment

Dataframe::Dataframe(Dataframe &&dataframe){
    _data = dataframe._data;

    dataframe._data.clear();
} // move

Dataframe &Dataframe::operator=(Dataframe&& dataframe){
    _data = dataframe._data;

    dataframe._data.clear();
} // move assignment

std::ostream &Dataframe::operator<<(std::ostream & Str) {
    for (std::shared_ptr<std::string> d: _data){
        Str << d << ", ";
    }
    Str << std::endl;
    return Str;
}