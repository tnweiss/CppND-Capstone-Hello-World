#include "source.h"

Source::Source(std::string sourceName){
    _keys = std::unique_ptr<std::vector<std::string>>(new std::vector<std::string>());
    _sourceName = sourceName;
}

Source::~Source() {

}

Source::Source(const Source& _source) {
    _keys = std::make_unique<std::vector<std::string>>();

    for (std::string key: *_source._keys) {
        _keys->push_back(key);
    }

    _sourceName = _source._sourceName;
}

Source Source::operator=(const Source& _source) {
    if (this == &_source) {
        return *this;
    }

    _keys = std::make_unique<std::vector<std::string>>();

    for (std::string key: *_source._keys) {
        _keys->push_back(key);
    }

     _sourceName = _source._sourceName;

    return *this;
}

Source::Source(Source &&source) {
    _sourceName = source._sourceName;
    _keys = std::move(source._keys);
    source._keys = nullptr;
}

Source &Source::operator=(Source &&source) {
    _sourceName = source._sourceName;
    _keys = std::move(source._keys);
    source._keys = nullptr;

    return *this;
}

int Source::GetKeyIndex(std::string keyName){
    for (int i=0; i<_keys->size(); i++) {
        if (_keys->at(i) == keyName){
            return i;
        }
    }

    return -1;
}

std::string Source::GetSourceName(){
    return _sourceName;
}

void Source::AddKey(std::string key) {
    _keys->push_back(key);
}