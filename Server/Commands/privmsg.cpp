#include "../Server.class.hpp"

std::string Server::privmsg(Client * client, Message & msg) {
  std::string response;
  std::vector<std::string> null_vector(0);
  if (msg.params.size() != 2) {
    response = generateResponse("ft_irc", "461", null_vector, "Not enough parameters");
    return (response);
  }
  std::vector<std::string> params;
  params.push_back("PRIVMSG");
  params.push_back(msg.params[0]);
  response = generateResponse(client->getIdentifier(), "", params, msg.params[1]);
  std::cout << response << std::endl;
  std::string channel_type = "#!&*";
  if (channel_type.find(msg.params[0][0]) != std::string::npos) {
    if (this->channelExists(msg.params[0])) {
      // get channel
      Channel * channel = this->getChannel(msg.params[0]);
      if (client->isInChannel(channel) == false) {
        params.clear();
        params.push_back(msg.params[0]);
        response = generateResponse("ft_irc", "404", params, "You are not on this channel");
        return (response);
      }
      // send to channel
      std::vector<Client *>::iterator it;
      std::vector<Client *> clients = channel->getClients();
      std::cout << "Clients in channel: " << clients.size() << std::endl;
      for (it = clients.begin(); it != clients.end(); ++it) {
        if ((*it)->getNickname() != client->getNickname())
          send((*it)->getSocket(), response.c_str(), response.length(), 0);
      }
    } else {
      response = generateResponse("ft_irc", "403", null_vector, "No such channel");
      return (response);
    }
  } else {
    // send to nickname
    Client * recipient = this->getClientByName(msg.params[0]);
    if (recipient != nullptr) {
      send(recipient->getSocket(), response.c_str(), response.length(), 0);
    } else {
      response = generateResponse("ft_irc", "401", null_vector, "No such nick");
      return (response);
    }
  }
  return ("");
}
