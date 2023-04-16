#include "../Server.class.hpp"

std::string Server::oper(Client * client, Message & msg) {
  std::vector<std::string> params;

  if (msg.params.size() != 2) {
    // params.clear();
    params.push_back(client->getNickname());
    params.push_back(client->getMode());
    return (generateResponse("ft_irc", "461", params, "Not enough parameters"));
  }
  if (msg.params[0] != "Oper42") {
    // params.clear();
    params.push_back(client->getNickname());
    // params.push_back(client->getMode());
    return (generateResponse("ft_irc", "464", params, "User incorrect"));
  }
  if (msg.params[1] != "ServTL") {
    // params.clear();
    params.push_back(client->getNickname());
    // params.push_back(client->getMode());
    return (generateResponse("ft_irc", "464", params, "Password incorrect"));
  }
  client->setMode("+o");
  client->setNickname("@Oper42");
  // params.clear();
  params.push_back(client->getNickname());
  params.push_back(client->getMode());
  return (generateResponse("ft_irc", "381", params, "You are now an IRC operator"));

}
