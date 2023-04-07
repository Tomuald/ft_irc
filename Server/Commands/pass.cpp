#include "../Server.class.hpp"

std::string Server::pass(Client * client, Message & msg) {
  std::vector<std::string> null_vector(0);
  if (msg.params.size() != 1) {
    return (generateResponse("ft_irc", "461", null_vector, "Not enough parameters"));
  }
  if (client->isRegistered() == true) {
    return (generateResponse("ft_irc", "462", null_vector, "You may not reregister"));
  }
  if (this->_password.compare(msg.params[0]) != 0)
    return (generateResponse("ft_irc", "464",  null_vector,"Password incorrect"));
  client->setPassword(msg.params[0]);
  return ("");
}
