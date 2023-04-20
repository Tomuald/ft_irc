#include "../Server.class.hpp"

std::string Server::who(Client * client, Message & msg) {
  // lists all users that match the given string
  std::string response;
  if (this->channelExists(msg.params[0])) {
    std::vector<std::string> params;
    Channel * channel = this->getChannel(msg.params[0]);
    if (!channel) {
      return ("");
    }
    std::vector<Client *>::iterator it;
    std::vector<Client *> clients = channel->getClients();
    for (it = clients.begin(); it != clients.end(); ++it) {
      if ((*it)->getNickname() == client->getNickname()) {
        continue ;
      }
      params.push_back(client->getNickname());
      params.push_back(channel->getName());
      params.push_back((*it)->getUsername());
      params.push_back((*it)->getIP());
      params.push_back("ft_irc");
      params.push_back((*it)->getNickname());
      response = generateResponse("ft_irc", "352", params, (*it)->getFullname());
      send(client->getSocket(), response.c_str(), response.length(), 0);
    }
    // Notify End of /WHO list
    params.clear();
    params.push_back(client->getNickname());
    params.push_back(msg.params[0]);
    response = generateResponse("ft_irc", "315", params, "End of /WHO list");
  }
  return (response);
}
