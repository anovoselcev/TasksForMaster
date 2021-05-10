#pragma once
#include <chrono>
#include <iostream>


namespace master {

    class Duration{
        std::chrono::time_point<std::chrono::steady_clock> start;
        const std::string  text;
        public:

        Duration(const std::string& str) : text(str){start = std::chrono::steady_clock::now();}
        ~Duration(){
            std::cout << text <<
                         ": " <<
                         std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start).count() <<
                         " us" <<
                         std:: endl;
        }

    };
}
