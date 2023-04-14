#include "../Server.class.hpp"

std::string Server::die(Client * client, Message & msg) {
  (void) client;
  (void) msg;
  exit(0);
  return ("");
}
