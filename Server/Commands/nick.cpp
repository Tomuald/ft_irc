#include "../Server.class.hpp"

std::string Server::nick(Client & client, Message & msg) {
  std::vector<std::string> null_vector(0);
  if (msg.params.size() != 1) {
    return (generateResponse("ft_irc", "431", null_vector, "No nickname given"));
  }
  // add other checks here...
  if (msg.params[0].length() > 9) {
    std::vector<std::string> _name;
    _name.push_back(msg.params[0]);
    return (generateResponse("ft_irc", "432",  _name, "Erroneous nickname"));
  }
  std::vector<Client>::iterator it;
  for (it = this->_userbase.begin(); it != this->_userbase.end(); ++it) {
    if (it->getNickname() == msg.params[0]) {
      std::vector<std::string> _name;
      _name.push_back(msg.params[0]);
      return (generateResponse("ft_irc", "433",  _name, "Nickname is already in use"));
    }
  }
  client.setNickname(msg.params[0]);
  return ("Nickname has been set!\r\n");
}
