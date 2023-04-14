#include "../Server.class.hpp"

std::string Server::part(Client * client, Message & msg) {
  std::string response;
  std::vector<std::string> params;

  if (msg.params.size() < 1) {
    params.push_back("PART");
    return (generateResponse("ft_irc", "461", params, "Not enough parameters"));
  }
  Channel * channel = this->getChannel(msg.params[0]);
  if (channel == nullptr) {
    params.push_back(msg.params[0]);
    return (generateResponse("ft_irc", "403", params, "No such channel"));
  }

  if (channel->removeClient(client) == false) {
    params.push_back(msg.params[0]);
    return (generateResponse(client->getIdentifier(), "442", params, "You're not on that channel"));
  }
  if (channel->getClients().size() == 0) {
    this->removeChannel(channel);
    params.push_back(channel->getName());
    response = generateResponse("ft_irc", "404", params, "No more users in channel");
    send(client->getSocket(), response.c_str(), response.length(), 0);
  }
  std::cout << "Num of channels: " << this->_channels.size() << std::endl;
  params.push_back(msg.params[0]);
  std::string message;
  if (msg.params.size() == 2) {
    message = msg.params[1];
  } else {
    message = client->getNickname();
  }
  response = generateResponse(client->getIdentifier(), "PART", params, message);
  std::vector<Client *> clients = channel->getClients();
  std::vector<Client *>::iterator it;
  for (it = clients.begin(); it != clients.end(); ++it) {
    send((*it)->getSocket(), response.c_str(), response.length(), 0);
  }
  client->quitChannel(channel);
  return (response);
}
