#include <iostream>

int main(void) {

    std::string name = "#hol#a";

    std::string ch_type = "#%L";
    std::size_t found = ch_type.find(name[0]);
    
    std::cout << "found = " << found << std::endl;
    
    return (0);
}