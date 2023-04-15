#include "../Server.class.hpp"

std::string Server::oper(Client * client, Message & msg) {
    std::cout << "aqui OPER nick = " << client->getNickname() << " CMD = " << msg.command << std::endl;
  std::vector<std::string> params;
  if (msg.params.size() != 2) {
    params.push_back(client->getNickname());
    params.push_back(client->getMode());
    return (generateResponse("ft_irc", "461", params, "Not enough parameters"));
  }
//   if (msg.params[0] != client->getNickname()) {
//     return (generateResponse("ft_irc", "502", params, ""));
//   }
//   client->setMode(msg.params[1]);
//   params.push_back(client->getNickname());
//   params.push_back(msg.params[1]);
  return (generateResponse("ft_irc", "221", params, ""));

}
