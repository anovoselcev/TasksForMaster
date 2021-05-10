#pragma once

#include <fstream>
#include <cstring>
#include <optional>
#include <functional>
#include <vector>

namespace master {

size_t pattern_offset(const std::string& pattern){
    size_t res = 0;
    for(const auto& it : pattern) if(it == '\n') res++;
#ifdef __MINGW32__
    res += 8;
#endif
    return res;
}

std::vector<size_t> prefix_function(const std::string& str){
    std::vector<size_t> pi(str.size(), 0);
    for(size_t i = 1; i < str.size(); ++i){
        size_t j = pi[i - 1];
        while(j && str[i] != str[j]) j = pi[j - 1];
        if(str[i] == str[j]) ++j;
        pi[i] = j;
    }
    return pi;
}


std::optional<size_t> kmp_file(const std::string& filename,
                               const std::string& pattern){
    if(filename.empty() || pattern.empty()) return std::nullopt;

    size_t size_pattern = pattern.size();
    auto pf = prefix_function(pattern);

    std::ifstream file(filename);
    char buffer;
    size_t k = 0;

    size_t sec_symbols = pattern_offset(pattern);

    while(!file.eof()){
        file.read(&buffer, 1);
        while(k && (pattern[k] != buffer)) k = pf[k - 1];
        if(pattern[k] == buffer) k++;
        if(size_pattern == k){
            size_t current = static_cast<size_t>(file.tellg()) - size_pattern - sec_symbols;
            file.close();
            return current;
        }

    }
    return std::nullopt;

}

std::optional<size_t> kmp(const std::string& text,
                          const std::string& pattern){
    if(text.empty() || pattern.empty()) return std::nullopt;

    size_t size_pattern = pattern.size();
    auto pf = prefix_function(pattern);

    size_t k = 0;

    size_t sec_symbols = pattern_offset(pattern);

    for(size_t i = 0; i < text.size(); ++i){
        while(k && (pattern[k] != text[i])) k = pf[k - 1];
        if(pattern[k] == text[i]) k++;
        if(size_pattern == k){
            return i - size_pattern - sec_symbols + 1;
        }

    }
    return std::nullopt;

}



std::optional<size_t> find(const std::string& text,
                           const std::string& pattern){
    return kmp(text, pattern);
}


std::optional<size_t> find_in_file(const std::string& filename,
                                   const std::string& pattern){
    return kmp_file(filename, pattern);
}



}
