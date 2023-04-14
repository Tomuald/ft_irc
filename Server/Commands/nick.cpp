#include "../Server.class.hpp"

std::string Server::nick(Client * client, Message & msg) {
  std::vector<std::string> params(0);
  if (msg.params.size() != 1) {
    return (generateResponse("ft_irc", "431", params, "No nickname given"));
  }
  // add other checks here...
  if (msg.params[0].length() > 9) {
    params.push_back(msg.params[0]);
    return (generateResponse("ft_irc", "432",  params, "Erroneous nickname"));
  }
  std::vector<Client *>::iterator it;
  for (it = this->_userbase.begin(); it != this->_userbase.end(); ++it) {
    if ((*it)->getNickname() == msg.params[0]) {
      params.push_back(msg.params[0]);
      return (generateResponse("ft_irc", "433", params, "Nickname is already in use"));
    }
  }
  client->setNickname(msg.params[0]);
  std::string old_identifier = client->getIdentifier();
  client->setFullIdentifier();
  params.push_back("NICK");
  params.push_back(client->getNickname());
  if (client->isRegistered() == false)
    return (generateResponse(client->getIdentifier(), "", params, ""));
  return (generateResponse(old_identifier, "", params, ""));
}
