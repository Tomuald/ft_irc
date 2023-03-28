#include <iostream>
#include "./Server/Server.class.hpp"

int main(int argc, char **argv) {
  if (argc != 3) {
    std::cerr << "usage: ./ircserv <port> <password>" << std::endl;
    return (-1);
  }
  (void) argv;
  std::cout << "Program Starting" << std::endl;
  Server server(argv[1], argv[2]);
  try {
    std::cout << "Starting server" << std::endl;
    server.start();
  }
  catch (std::exception e) {
    std::cerr << e.what() << std::endl;
  }
  return (0);
}
