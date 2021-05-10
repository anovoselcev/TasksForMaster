#pragma once
#include <vector>
#include <string>
#include <numeric>
#include <stdexcept>

namespace master {

class KeyGen{
    const std::vector<int> checkers;

    void checkValid(const std::string& str){
        for(size_t i = 0; i < str.size(); ++i){
            if(str[i] < 'A' || str[i] > 'Z') throw std::invalid_argument("Wrong name. Name must be between A-z");
        }
    }

public:

    KeyGen() = delete;

    KeyGen(const std::initializer_list<int>& values) : checkers(values) {}

    KeyGen(const std::vector<int>& values) : checkers(values) {}

    size_t generate(const std::string& name){
         checkValid(name);
         size_t result  = std::accumulate(name.begin(), name.end(), 0);
         for(const auto& val : checkers) result ^= val;
         return result;
    }
};
}
