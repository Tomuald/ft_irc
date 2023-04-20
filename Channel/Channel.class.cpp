#include "Channel.class.hpp"

Channel::Channel(void) {
  this->_name = "no name";
  this->_clientsConnected = std::vector<Client *>();
  return ;
}

Channel::Channel(std::string name) {
  this->_name = name;
  this->_clientsConnected = std::vector<Client *>();
  this->_topic = "This is a default topic!";
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

std::vector<Client *> & Channel::getClients(void) {
  return (this->_clientsConnected);
}

std::string Channel::getTopic(void) const {
  return (this->_topic);
}

std::string Channel::getMode(void) const {
  return (this->_mode);
}

// Setters
void Channel::addClient(Client * client) {
  if (!client->isInChannel(this))
    this->_clientsConnected.push_back(client);
}

bool Channel::removeClient(Client * client) {
  std::vector<Client *>::iterator it = this->_clientsConnected.begin();
  while (it != this->_clientsConnected.end()) {
    if ((*it)->getNickname() == client->getNickname()) {
      it = this->_clientsConnected.erase(it);
      return (true);
    } else {
      ++it;
    }
  }
  return (false);
}

bool Channel::checkClientConnected(Client * client) {
  std::vector<Client *>::iterator it = this->_clientsConnected.begin();
  while (it != this->_clientsConnected.end()) {
    if ((*it)->getNickname() == client->getNickname()) {
      return (true);
    } else {
      ++it;
    }
  }
  return (false);
}

void  Channel::setTopic(std::string topic) {
  this->_topic = topic;
}

void  Channel::setMode(std::string mode) {
  this->_mode = mode;
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
