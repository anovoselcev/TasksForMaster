#include <iostream>
#include <cstring>

#include <KeyGen.hpp>


int main(){
    master::KeyGen kg({0x5678, 0x1234});
    std::string name;
    while(std::getline(std::cin, name, '\n')){
        try{
            if(name.empty()) break;;
            size_t key = kg.generate(name);
            std::cout << key << std::endl;
        }
        catch(std::invalid_argument& e){
            std::cout << "Error: " << e.what() << std::endl;
        }
    }
    return 0;
}
