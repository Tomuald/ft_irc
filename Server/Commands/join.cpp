#include "../Server.class.hpp"

std::string Server::join(Client * client, Message & msg) {
  std::string response;
  std::vector<std::string> params;

  if (msg.params.size() == 0 || (msg.params[0].length() == 1 && msg.params[0][0] == '#')) {
    params.push_back("JOIN");
    response = generateResponse("ft_irc", "461", params, "Not enough parameters");
    return (response);
  }
  std::string channel_name = msg.params[0];
  Channel * channel = this->getChannel(channel_name);
  if (channel == nullptr) {
    params.push_back(channel_name);
    return (generateResponse("ft_irc", "403", params, "No such channel"));
  }
  channel->addClient(client);

  // Notify the channel that a new client has joined
  params.push_back("JOIN");
  params.push_back(channel_name);
  response = generateResponse(client->getIdentifier(), "", params, "");
  std::vector<Client *>::iterator it;
  std::vector<Client *> clients = channel->getClients();
  for (it = clients.begin(); it != clients.end(); ++it) {
    send((*it)->getSocket(), response.c_str(), response.length(), 0);
  }

  // Notify the user of the channel details
  params.clear();
  params.push_back(client->getNickname());
  params.push_back(channel_name);
  response = generateResponse("ft_irc", "332", params, channel->getTopic());
  send(client->getSocket(), response.c_str(), response.length(), 0);

  // Notify the user of other users in the channel
  params.clear();
  params.push_back(client->getNickname());
  params.push_back("=");
  params.push_back(channel_name);
  std::string nicknames;
  for (it = clients.begin(); it != clients.end(); ++it) {
    if ((*it)->isOperator()) {
      nicknames += "@";
    }
    nicknames += (*it)->getNickname();
    std::vector<Client *>::iterator next_it = it;
    std::advance(next_it, 1);
    if (next_it != clients.end()) {
      nicknames += " ";
    }
  }
  response = generateResponse("ft_irc", "353", params, nicknames);
  send(client->getSocket(), response.c_str(), response.length(), 0);
  // Notify End of /NAMES list
  params.clear();
  params.push_back(client->getNickname());
  params.push_back(channel_name);
  response = generateResponse("ft_irc", "366", params, "End of /NAMES list");
  client->joinChannel(channel);
  return (response);
}
