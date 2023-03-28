#include "Client.class.hpp"

Client::Client(void) {
  this->_socket = -1;
  this->_operator = false;
  this->_isRegistered = false;
  return ;
}

Client::Client(int const socket) : _socket(socket) {
  this->_operator = false;
  this->_isRegistered = false;
}

Client::Client(Client const & src) {
  this->_socket = src._socket;
  this->_nickname = src._nickname;
  this->_username = src._username;
  this->_password = src._password;
  this->_operator = src._operator;
  this->_isRegistered = src._isRegistered;
  this->_ip = src._ip;
  return ;
}

Client::~Client(void) { return ; }

Client & Client::operator=(Client const & rhs) {
  if (this != &rhs) {
    this->_socket = rhs._socket;
    this->_nickname = rhs._nickname;
    this->_username = rhs._username;
    this->_password = rhs._password;
    this->_operator = rhs._operator;
    this->_isRegistered = rhs._isRegistered;
    this->_ip = rhs._ip;
  }
  return (*this);
}

// Getters
std::string Client::getUsername(void) const {
  return (this->_username);
}

std::string Client::getNickname(void) const {
  return (this->_nickname);
}

int Client::getSocket(void) const {
  return (this->_socket);
}

// Checkers
bool Client::isRegistered(void) const {
  return (this->_isRegistered);
}

bool Client::passwordIsSet(void) const {
  if (this->_password.empty()) {
    return (false);
  }
  return (true);
}

std::string Client::getIP(void) const {
  return (this->_ip);
}

// Setters
void Client::setNickname(std::string nickname) {
  if (nickname.empty()) {
    return ;
  } else {
    this->_nickname = nickname;
  }
  return ;
}

void Client::setUsername(std::string username) {
  if (username.empty()) {
    return ;
  } else {
    this->_username = username;
  }
  return ;
}

void Client::setRealname(std::string realname) {
  if (realname.empty()) {
    return ;
  } else {
    this->_realname = realname;
  }
  return ;
}

void Client::setPassword(std::string password) {
  if (password.empty()) {
    return ;
  } else {
    this->_password = password;
  }
  return ;
}

void Client::setRegistered(void) {
  this->_isRegistered = true;
}

void Client::setIP(std::string ip) {
  this->_ip = ip;
}

std::ostream & operator<<(std::ostream & o, Client const & i) {
  o << i.getUsername();
  return (o);
}
