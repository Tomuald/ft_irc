#ifndef CLIENT_CLASS_HPP_
# define CLIENT_CLASS_HPP_

#include <string>
#include <iostream>

class Client {
public:
  Client(void);
  Client(int const socket);
  Client(Client const & src);
  ~Client(void);

  Client& operator=(Client const & rhs);

  // Getters
  std::string getUsername(void) const;
  std::string getNickname(void) const;
  int getSocket(void) const;
  std::string getIP(void) const;

  // Checkers
  bool isRegistered(void) const;
  bool passwordIsSet(void) const;

  // Setters
  void setNickname(std::string nickname);
  void setRealname(std::string realname);
  void setPassword(std::string password);
  void setRegistered(void);
  void setUsername(std::string username);
  void setIP(std::string ip);
private:
  int _socket;
  std::string _nickname;
  std::string _username;
  std::string _password;
  std::string _realname;
  std::string _ip;
  bool _operator;
  bool _isRegistered;
};

std::ostream & operator<<(std::ostream & o, Client const & i);
#endif // CLIENT_CLASS_HPP_
