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

  // Channel channel = server.getChannel("test");
  // Client client1(1);
  // Client client2(2);
  // Client client3(3);
  // client1.setNickname("client1");
  // client2.setNickname("client2");
  // client2.setNickname("client3");

  // channel.addClient(client1);
  // channel.addClient(client2);
  // channel.addClient(client3);
  // server.addChannel(channel);
  // std::cout << "size: " << server.getChannel("test").getClients().size() << std::endl;
  // exit(1);
  try {
    std::cout << "Starting server" << std::endl;
    server.start();
  }
  catch (std::exception e) {
    std::cerr << e.what() << std::endl;
  }
  return (0);
}
