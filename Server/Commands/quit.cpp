#include "../Server.class.hpp"

std::string Server::quit(Client * client, Message & message) {
  std::vector<std::string> null_vector(0);
  std::vector<Client *>::iterator it;
  std::cout << "Server had: " << this->_userbase.size() << " users" << std::endl;
  for (it = this->_userbase.begin(); it != this->_userbase.end(); ) {
    if ((*it)->getNickname() == client->getNickname()) {
      // std::cout << "found the client!" << std::endl;
      std::vector<Channel *>::iterator it2;
      for (it2 = (*it)->getChannels().begin(); it2 != (*it)->getChannels().end(); ++it2) {
        (*it2)->removeClient(client);
      }
      close(client->getSocket());
      delete (*it);
      it = this->_userbase.erase(it);
    } else {
      ++it;
    }
  }
  (void) message;
  return ("");
}
