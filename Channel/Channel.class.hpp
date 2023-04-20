#ifndef CHANNEL_CLASS_HPP_
# define CHANNEL_CLASS_HPP_

# include <iostream>
# include <vector>

# include "../Client/Client.class.hpp"
//# include "../Server/Server.class.hpp"
class Client;
class Server;

class Channel {
public:
  Channel(void);
  Channel(std::string name);
  Channel(Channel const & src);
  ~Channel(void);

  Channel& operator=(Channel const & rhs);

  // Getters
  std::string getName(void) const;
  Client getClient(std::string name);
  std::vector<Client *> & getClients(void);
  std::string getTopic(void) const;
  std::string getMode(void) const;
  // Checkers
  bool channelExists(std::string name) const;
  // Setters
  void addClient(Client * client);
  bool removeClient(Client * client);
  bool checkClientConnected(Client * client);
  void  setTopic(std::string topic);
  void  setMode(std::string mode);
  // Utils
private:
  std::string _name;
  std::string _topic;
  std::string _mode;
  std::vector<Client *> _clientsConnected;
};

std::ostream & operator<<(std::ostream & o, Channel const & i);
#endif // CHANNEL_CLASS_HPP_
