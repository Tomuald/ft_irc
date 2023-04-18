#include "../Server.class.hpp"

/**
  * @brief  The TOPIC message is used to change or view the topic of a channel.

  Command: TOPIC
  Parameters: <channel> [<topic>]

  Eje:
  TOPIC #test :another topic      ;set the topic on #test to "another
                                   topic".

   TOPIC #test                     ; check the topic for #test.
*/

std::string Server::topic(Client * client, Message & msg) {
  std::vector<std::string> params;

  if (msg.params.size() == 0) {
    params.push_back("TOPIC");
    return (generateResponse("ft_irc", "461", params, "Not enough parameters"));
  }
  std::string channel_name = msg.params[0];
  Channel * channel = this->getChannel(channel_name);
 
  if (channel == nullptr) {
    params.push_back(channel_name);
    return (generateResponse("ft_irc", "403", params, "No such channel"));
  }
  if (msg.params.size() == 1) {
    if (channel->getTopic().empty())
			return (generateResponse("ft_irc", "331", params, " No topic is set"));
    params.push_back("TOPIC");
    params.push_back(channel_name);
    return (generateResponse("ft_irc", "332", params, channel->getTopic()));
  }
  if (msg.params.size() == 2) {
    if (client->isOper() == false) {
      params.push_back("TOPIC");
      params.push_back(client->getNickname());
      return (generateResponse("ft_irc", "482", params, "You're not channel operator"));
    }
    else if (client->isInChannel(channel) == false) {
      params.push_back(msg.params[0]);
      return (generateResponse("ft_irc", "404", params, "Cannot send to channel"));
    }
    else {
      std::string response;

      channel->setTopic(msg.params[1]);
      // Notify the channel New TOPIC
      params.push_back("TOPIC");
      params.push_back(channel_name);
      response = generateResponse(client->getIdentifier(), "", params, channel->getTopic());
      std::vector<Client *>::iterator it;
      std::vector<Client *> clients = channel->getClients();
      for (it = clients.begin(); it != clients.end(); ++it)
        send((*it)->getSocket(), response.c_str(), response.length(), 0);
      params.clear();
      params.push_back("TOPIC");
      return (generateResponse("ft_irc", "332", params, channel->getTopic()));
    }
  }
  return ("");
}
