#include "../Server.class.hpp"

std::string Server::pong(Client * client, Message & msg) {
  std::string response;
  std::vector<std::string> null_vector(0);
  if (msg.params.size() < 1) {
    response = generateResponse("ft_irc", "461", null_vector, "Need more parameters");
    return (response);
  }
  response = generateResponse(client->getIP(), "PONG", msg.params, "");
  return (response);
}
