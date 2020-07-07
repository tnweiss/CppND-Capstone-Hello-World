#ifndef ENGINE_H
#define ENGINE_H

#include <future>
#include <vector>
#include <thread>
#include <ostream>
#include <mutex>

#include "query.h"

template <class T>
class ConcurrentList {
    public:
        ConcurrentList(std::vector<T> d) {
            _list = d;
        }
        ConcurrentList(){}
        bool empty(){
            std::lock_guard<std::mutex> lock(_mutex);
            return _list.empty();
        }
        int size(){
            return _list.size();
        }
        void push(T item){
            std::lock_guard<std::mutex> lock(_mutex);
            _list.push_back(item);
        }
        T pop(){
            std::lock_guard<std::mutex> lock(_mutex);
            T item = _list.back();
            _list.pop_back();
            return item;
        }
    
    private:
        std::vector<T> _list;
        std::mutex _mutex;
};

class Engine {
    public:
        Engine(Query*, std::vector<std::string>);
        void start(int);
        void blockForResults();
        void addResult(Dataframe);
        void executeQuery();
        friend std::ostream &operator<<(std::ostream & Str, const Engine& e){
            return Str;
        }

    private:
        Query *_query;
        ConcurrentList<std::string> _files;
        std::vector<std::thread> _threads;
        ConcurrentList<Dataframe> _results;
};

#endif