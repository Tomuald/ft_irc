#include "../Server.class.hpp"

std::string Server::quit(Client * client, Message & message) {
  std::vector<std::string> null_vector(0);
  std::vector<Client *>::iterator it;
  for (it = this->_userbase.begin(); it != this->_userbase.end(); ++it) {
    if ((*it)->getSocket() == client->getSocket()) {
      close(client->getSocket());
      this->_userbase.erase(it);
      break ;
    }
  }
  std::vector<std::string> params;
  params.push_back(client->getNickname());
  params.push_back(message.command);
  if (message.params.size() == 1)
    params.push_back(message.params[0]);
  std::string response = generateResponse("ft_irc", "", params, "");
  return (response);
}
