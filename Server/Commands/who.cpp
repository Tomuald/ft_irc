#include "../Server.class.hpp"

std::string Server::who(Client * client, Message & msg) {
  // lists all users that match the given string
  std::string name = msg.params[0];
  std::vector<std::string> userlist;
  std::vector<Client *>::iterator it;
  for (it = this->_userbase.begin(); it != this->_userbase.end(); ++it) {
    std::string comp = (*it)->getNickname();
    if (comp.c_str(), name.c_str(), name.length())
      userlist.push_back(comp);
  }
  std::string response = generateResponse("ft_irc", "352", userlist, "");
  send(client->getSocket(), response.c_str(), response.length(), 0);
  std::vector<std::string> _name;
  _name.push_back(userlist.back());
  response = generateResponse("ft_irc", "315", _name, "End of /WHO list");
  return (response);
}
