#include "Server.class.hpp"

//////////////////////////////////////////////
// Constructors, Destructors, & Coplien stuff
//////////////////////////////////////////////
Server::Server(std::string port, std::string pass) : _port(port), _password(pass) {
  return;
}

Server::Server(Server const & src) {
  this->_channels = src._channels;
  return ;
}

Server & Server::operator=(Server const & rhs) {
  if (this != &rhs) {
    this->_channels = rhs._channels;
  }
  return (*this);
}

Server::~Server(void) {return;}

///////////////
// Registration
///////////////

void Server::registerClient(Client * client) {
  if (this->informationValid(client) && client->passwordIsSet() == true) {
    std::vector<std::string> params;
    params.push_back(client->getNickname());
    client->setRegistered();
    // this->addClient(client);
    std::string welcome = "Welcome to ft_irc " + client->getIdentifier();
    std::string response = generateResponse("ft_irc", "001",  params, welcome);
    send(client->getSocket(), response.c_str(), response.length(), 0);
  } else {
    std::vector<std::string> null_vector(0);
    std::string response = generateResponse("ft_irc", "464", null_vector, "Registration failed");
    send(client->getSocket(), response.c_str(), response.length(), 0);
    Message msg;
    this->quit(client, msg);
    this->removeClient(client);
  }
  return ;
}

///////////
// Setters
///////////

void Server::addChannel(Channel * channel) {
  this->_channels.push_back(channel);
}

void Server::addClient(Client * client) {
  this->_userbase.push_back(client);
}

void Server::removeClient(Client * client) {
  std::vector<Client *>::iterator it = this->_userbase.begin();
  while (it != this->_userbase.end()) {
    if ((*it)->getSocket() == client->getSocket()) {
      it = this->_userbase.erase(it);
      delete *it;
    } else {
      it++;
    }
  }
}
///////////
// Checkers
///////////

bool Server::channelExists(std::string const name) const {
  std::vector<Channel *>::const_iterator it;
  for (it = this->_channels.begin(); it != this->_channels.end(); ++it) {
    std::cout << "Channel name: " << (*it)->getName() << std::endl;
    if ((*it)->getName() == name) {
      return (true);
    }
  }
  return (false);
}

bool Server::clientRegistered(int socket) const {
  std::vector<Client *>::const_iterator it = this->_userbase.begin();
  for (it = this->_userbase.begin(); it != this->_userbase.end(); ++it) {
    const Client * obj = *it;
    if (obj->getSocket() == socket) {
      return (true);
    }
  }
  return (false);
}

bool Server::informationValid(Client * client) const {
  if (!client->getUsername().empty() && \
      !client->getNickname().empty()) {
      // client->passwordIsSet() == true) {
    return (true);
  }
  return (false);
}

//////////
// Getters
//////////

Client * Server::getClientBySocket(int socket) {
  std::vector<Client *>::iterator it = this->_userbase.begin();
  for (it = this->_userbase.begin(); it != this->_userbase.end(); ++it) {
    Client * obj = *it;
    if (obj->getSocket() == socket) {
      return (obj);
    }
  }
  // return a null object if not found
  return (nullptr);
}

Client * Server::getClientByName(std::string name) {
  std::vector<Client *>::iterator it = this->_userbase.begin();
  for (it = this->_userbase.begin(); it != this->_userbase.end(); ++it) {
    Client * obj = *it;
    if (obj->getNickname() == name) {
      return (obj);
    }
  }
  // return a null object if not found
  return (nullptr);
}

Channel * Server::getChannel(std::string & name) {
  std::vector<Channel *>::iterator it;
  for (it = this->_channels.begin(); it != this->_channels.end(); ++it) {
    if ((*it)->getName() == name) {
      return (*it);
    }
  }
  std::string channel_types = "#!&*";
  if (channel_types.find(name[0]) == std::string::npos)
    return (nullptr);
  Channel * channel = new Channel(name);
  this->addChannel(channel);
  return (channel);
}

void Server::removeChannel(Channel * channel) {
  std::vector<Channel *>::iterator it = this->_channels.begin() ;
  while (it != this->_channels.begin()) {
    if ((*it) == channel) {
      delete *it;
      it = this->_channels.erase(it);
    } else {
      ++it;
    }
  }
}

///////////////
// Server setup
///////////////

int Server::makeServerSocket(void) {

  this->_server_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (this->_server_socket == -1) {
    throw std::exception();
  }
  std::cout << "socket created" << std::endl;

  int optval = 1;
  socklen_t optlen = sizeof(optval);
  if (setsockopt(this->_server_socket, SOL_SOCKET, SO_REUSEADDR, &optval, optlen) < 0) {
    return (-1);
  }

  // set up addresses for binding
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(atoi(this->_port.c_str()));
  addr.sin_addr.s_addr = INADDR_ANY;

  if (bind(this->_server_socket, (struct sockaddr *) &addr, sizeof(addr)) == -1) {
    std::cout << strerror(errno) << std::endl;
    return (-1);
  }
  std::cout << "socket bound" << std::endl;

  int flags = fcntl(this->_server_socket, F_GETFL, 0);
  fcntl(this->_server_socket, F_SETFL, flags | O_NONBLOCK);

  if (listen(this->_server_socket, 10) == -1) {
    std::cout << strerror(errno) << std::endl;
    return (-1);
  }
  std::cout << "socket listening" << std::endl;

  return (0);
}

int Server::setUpKQ(void) {
  // set up a kqueue
  this->_kq = kqueue();
  if (this->_kq < 0) {
    std::cerr << strerror(errno) << std::endl;
    return (-1);
  }
  // set up kevent
  struct kevent event;
  EV_SET(&event, this->_server_socket, EVFILT_READ, EV_ADD, 0, 0, NULL);
  if (kevent(this->_kq, &event, 1, NULL, 0, NULL) < 0) {
    std::cerr << strerror(errno) << std::endl;
    return (-1);
  }
  return (0);
}


void Server::start(void) {
  // ensayo leo
  struct sockaddr_in struct_client;
  unsigned len = 0;

  // init a server socket
  if (this->makeServerSocket() == -1) {
    throw std::exception();
  }
  // init a kqueue
  if (this->setUpKQ() == -1) {
    throw std::exception();
  }
  // main server loop
  while (true) {
    // make this dynamic or larger
    struct kevent events[16];

    int num_events = kevent(this->_kq, NULL, 0, events, 16, NULL);
    if (num_events == -1) {
      std::cerr << strerror(errno) << std::endl;
      throw std::exception();
    }

    for (int i = 0; i < num_events; i++) {
      int socket = events[i].ident;
      if (socket == this->_server_socket) {
           // new connection
           std::cout << "registering new connection" << std::endl;
           int accept_socket = accept(this->_server_socket, (struct sockaddr *) &struct_client, &len); //leo
           if (accept_socket == -1) {
               std::cerr << strerror(errno) << std::endl;
               continue;
           }
           EV_SET(&this->_event, accept_socket, EVFILT_READ, EV_ADD, 0, 0, NULL);
           if (kevent(this->_kq, &this->_event, 1, NULL, 0, NULL) < 0) {
             std::cerr << "Error: Failed to add client socket to kqueue." << std::endl;
             close(accept_socket);
             continue;
           }
       } else {
        // handle data on client socket
        std::cout << "handling client request" << std::endl;
        char buffer[512];
        int nbytes = recv(events[i].ident, buffer, sizeof(buffer), 0);
        if (nbytes > 512) {
          buffer[511] = '\0';
        } else {
          buffer[nbytes] = '\0';
        }
        if (nbytes < 0) {
           std::cerr << "Error: Failed to receive data from client socket." << std::endl;
           close(events[i].ident);
           continue;
        } else if (nbytes == 0) {
           // Client has disconnected
           close(events[i].ident);
           continue;
        } else
          this->handlePartialReq(buffer);
        
        // if (this->_line.find('\n') != std::string::npos) {
        if (this->_line[_line.length() - 1] == '\n') {
          this->handleRequest(socket, this->_line);
          this->_line.clear();
        }

        memset(buffer, 0, sizeof(*buffer));
      }
    }
  }
  close(this->_server_socket);
}

//////////
// Parsing
//////////

std::vector<Message> Server::parse(std::string input) {
  std::vector<Message> messages;
  // std::string input(buffer);
  std::istringstream iss(input);

  std::string line;
  while (std::getline(iss, line)) {
    Message msg(line);
    messages.push_back(msg);
  }
  return (messages);
}

// TO process a command, first aggregate the received packets in order to rebuild LIne
void Server::handlePartialReq(char buffer[512]) {

  std::string partial_line(buffer);

  this->_line.append(partial_line);
  // std::cout << "_LIne = " << this->_line << std::endl;
}

////////////////////
// Message execution
////////////////////
std::string Server::execute(Client * client, Message & msg) {
  std::map<std::string, fctPointer> functionMap = this->getFunctionMap();
  std::vector<std::string> null_vector(0);
  std::map<std::string, fctPointer>::iterator it;
  bool found = false;

  std::string response;
  for (it = functionMap.begin(); it != functionMap.end(); ++it) {
    if (msg.command == it->first) {
      fctPointer func = it->second;
      std::cout << "Executing: " << it->first << std::endl;
      response = (this->*func)(client, msg);
      found = true;
    }
  }
  if (found == false) {
    null_vector.push_back(client->getIdentifier());
    null_vector.push_back("Unknown command");
    return (generateResponse("ft_irc", "421", null_vector, ""));
  }
  return (response);
}

void Server::handleRequest(int socket, std::string buffer) {
  std::cout << "buffer = " << buffer << std::endl;
  Client * client;
  bool register_client = false;

  client = this->getClientBySocket(socket);
  std::vector<Message> messages = this->parse(buffer);
  if (client == nullptr) {
    client = new Client(socket);
    this->addClient(client);
    register_client = true;
  }
  std::vector<Message>::iterator it;
  for (it = messages.begin(); it != messages.end(); ++it) {
    std::cout << (*it) << std::endl;
    std::string response = this->execute(client, (*it));
    std::cout << response << std::endl;
    send(socket, response.c_str(), response.length(), 0);
    }
  if (informationValid(client) && !client->isRegistered()) {
    this->registerClient(client);
    register_client = false;
  }
  std::cout << "Server now has: " << this->_userbase.size() << " users" << std::endl;
}

// consider building this in your constructors!
std::map<std::string, Server::fctPointer> Server::getFunctionMap(void) {

  std::map<std::string, fctPointer> functionMap;
  // basic functions
  functionMap.insert(make_pair("PASS", &Server::pass));
  functionMap.insert(make_pair("QUIT", &Server::quit));
  functionMap.insert(make_pair("JOIN", &Server::join));
  functionMap.insert(make_pair("PRIVMSG", &Server::privmsg));
  functionMap.insert(make_pair("PING", &Server::pong));
  functionMap.insert(make_pair("WHO", &Server::who));
  functionMap.insert(make_pair("PART", &Server::part));
  functionMap.insert(make_pair("NICK", &Server::nick));
  functionMap.insert(make_pair("MODE", &Server::mode));
  functionMap.insert(make_pair("USER", &Server::user));
  functionMap.insert(make_pair("userhost", &Server::user));
  functionMap.insert(make_pair("die", &Server::die));
  // operator functions
  functionMap.insert(make_pair("OPER", &Server::oper));
  functionMap.insert(make_pair("KICK", &Server::kick));
  functionMap.insert(make_pair("TOPIC", &Server::topic));

  return (functionMap);
}
