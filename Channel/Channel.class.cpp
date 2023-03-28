#include "Channel.class.hpp"

Channel::Channel(void) { return ; }

Channel::Channel(std::string name) {
  this->_name = name;
  return ;
}

Channel::Channel(Channel const & src) {
  this->_name = src._name;
  this->_clientsConnected = src._clientsConnected;
  return ;
}

Channel::~Channel(void) { return ; }

// Getters
std::string Channel::getName(void) const {
  return (this->_name);
}

std::vector<Client> & Channel::getClients(void) {
  return (this->_clientsConnected);
}

// Setters
void Channel::addClient(Client const & client) {
  // std::vector<Client>::const_iterator it;
  // for (it = this->_clientsConnected.begin(); it != this->_clientsConnected.end(); ++it) {
  //   if (it->getNickname() == client.getNickname()) {
  //     return ;
  //   }
  // }
  std::cout << "before: " << this->_clientsConnected.size() << std::endl;
  this->_clientsConnected.push_back(client);
  std::cout << "after: " << this->_clientsConnected.size() << std::endl;
}

Channel & Channel::operator=(Channel const & rhs) {
  if (this != &rhs) {
    this->_name = rhs._name;
    this->_clientsConnected = rhs._clientsConnected;
  }
  return (*this);
}

std::ostream & operator<<(std::ostream & o, Channel const & i) {
  o << i.getName();
  return (o);
}
