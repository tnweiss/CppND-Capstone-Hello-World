#include "dataframe.h"

#include <sstream>
#include <vector>

#include "common.h"

Dataframe::Dataframe(std::string dataLine){
    _data = splitSharedPtr(dataLine, '\t');
}

Dataframe::Dataframe(std::vector<std::shared_ptr<std::string>> data) {
    this->_data  = data;
}

Dataframe::~Dataframe(){

}

std::shared_ptr<std::string> Dataframe::get(int index) {
    return _data.at(index);
}


Dataframe::Dataframe(const Dataframe& dataframe){
    _data = dataframe._data;
} // copy constructor

Dataframe Dataframe::operator=(const Dataframe& dataframe){
    if( this == &dataframe) {
        return *this;
    }

    _data = dataframe._data;

    return *this;
} //copy assignment

Dataframe::Dataframe(Dataframe &&dataframe){
    _data = dataframe._data;

    dataframe._data.clear();
} // move

Dataframe &Dataframe::operator=(Dataframe&& dataframe){
    _data = dataframe._data;

    dataframe._data.clear();

    return *this;
} // move assignment

std::ostream &Dataframe::operator<<(std::ostream & Str) {
    for (std::shared_ptr<std::string> d: _data){
        Str << d << ", ";
    }
    Str << std::endl;
    return Str;
}