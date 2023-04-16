#include <iostream>
#include <sstream>

int main(void) {
    char buff[100] = "Hola mundo 123";

    std::istringstream iss(buff);
    int n;
    std::string cadena;

    iss >> cadena >> n;

    std::cout << "cad  = " << cadena << " no = " << n << std::endl;

   

    return (0);
}