#include "../Server.class.hpp"

/**
  * @brief The MODE command is a dual-purpose command in IRC.  It allows both
  usernames and channels to have their mode changed.

  Command: MODE

  * Channel modes
  Parameters: <channel> {[+|-]|o|p|s|i|t|n|b|v} [<limit>] [<user>]
               [<ban mask>]

  * User modes
  Parameters: <nickname> {[+|-]|i|w|s|o}
*/
 

std::string Server::mode(Client * client, Message & msg) {
  std::vector<std::string> params;
  if (msg.params.size() != 2) {
    params.push_back(client->getNickname());
    params.push_back(client->getMode());
    return (generateResponse("ft_irc", "461", params, "Not enough parameters"));
  }
  std::string channel_types = "#!&*";
  if (channel_types.find(msg.params[0][0]) != std::string::npos) {
    // std::cout << "Segun ARG es un Channel\n";
    std::string channel_name = msg.params[0];
     Channel * channel = this->getChannel(channel_name);
     if (client->isOper() == false) {
      params.push_back("MODE");
      params.push_back(client->getNickname());
      return (generateResponse("ft_irc", "482", params, "You're not channel operator"));
    }
    else if (client->isInChannel(channel) == false) {
      params.push_back(msg.params[0]);
      return (generateResponse("ft_irc", "404", params, "Cannot send to channel"));
    }
    else {
      std::string response;
      std::string ch_modes = "opsitnbv";
      if (ch_modes.find(msg.params[1][1]) == std::string::npos) {
        params.push_back("MODE");
        params.push_back(channel_name);
        return(generateResponse("ft_irc", "501", params, "Unknown MODE flag"));
      }
      channel->setMode(msg.params[1]);
      // Notify the channel New TOPIC
      params.push_back("MODE");
      params.push_back(channel_name);
      response = generateResponse(client->getIdentifier(), "", params, channel->getMode());
      std::vector<Client *>::iterator it;
      std::vector<Client *> clients = channel->getClients();
      for (it = clients.begin(); it != clients.end(); ++it)
        send((*it)->getSocket(), response.c_str(), response.length(), 0);
      params.clear();
      params.push_back("MODE");
      return (generateResponse("ft_irc", "324", params, channel->getMode()));
    }
  }
  else {
    // std::cout << "Segun ARG es un nickName\n";
    if (msg.params[0] != client->getNickname()) {
      params.push_back(client->getNickname());
      return (generateResponse("ft_irc", "502", params, "Cant change mode for other users"));
    }
    client->setMode(msg.params[1]);
    params.push_back(client->getNickname());
    params.push_back(client->getMode());
    return (generateResponse("ft_irc", "221", params, ""));
  }
  return ("");
}
