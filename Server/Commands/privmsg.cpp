#include "../Server.class.hpp"

std::string Server::privmsg(Client & client, Message & msg) {
  std::string response;
  std::vector<std::string> null_vector(0);
  if (msg.params.size() != 2) {
    response = generateResponse("ft_irc", "461", null_vector, "Not enough parameters");
    return (response);
  }
  std::vector<std::string> _message;
  _message.push_back(msg.params[1]);
  response = generateResponse(client.getNickname(), "<" + client.getNickname() + ">", _message, "");
  if (msg.params[0][0] == '#') {
    if (this->channelExists(msg.params[0])) {
    // send to channel
      Channel & channel = this->getChannel(msg.params[0]);
      std::vector<Client>::iterator it;
      std::vector<Client> clients = channel.getClients();
      std::cout << "Clients in channel: " << clients.size() << std::endl;
      for (it = clients.begin(); it != clients.end(); ++it) {
        send(it->getSocket(), response.c_str(), response.length(), 0);
      }
    } else {
      response = generateResponse("ft_irc", "403", null_vector, "No such channel");
      return (response);
    }
  } else {
    // send to nickname
    Client & recipient = this->getClientByName(msg.params[0]);
    if (!recipient.getNickname().empty()) {
      send(recipient.getSocket(), response.c_str(), response.length(), 0);
    } else {
      response = generateResponse("ft_irc", "401", null_vector, "No such nick");
      return (response);
    }
  }
  return ("\r\n");
}
