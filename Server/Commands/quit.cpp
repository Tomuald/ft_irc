#include "../Server.class.hpp"

std::string Server::quit(Client * client, Message & message) {
  std::vector<std::string> null_vector(0);
  std::vector<Client *>::iterator it;
  std::cout << "Server had: " << this->_userbase.size() << " users" << std::endl;
  for (it = this->_userbase.begin(); it != this->_userbase.end(); ) {
    if ((*it)->getNickname() == client->getNickname()) {
      std::cout << "found the client!" << std::endl;
      close(client->getSocket());
      delete (*it);
      it = this->_userbase.erase(it);
    } else {
      ++it;
    }
  }
  std::cout << "Server now has: " << this->_userbase.size() << " users" << std::endl;
  (void) message;
  // std::vector<std::string> params;
  // params.push_back(client->getNickname());
  // params.push_back(message.command);
  // if (message.params.size() == 1)
  //   params.push_back(message.params[0]);
  // std::string response = generateResponse("ft_irc", "", params, "");
  return ("");
}
