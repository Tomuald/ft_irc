#ifndef SERVER_CLASS_HPP_
# define SERVER_CLASS_HPP_

# include <sys/types.h>
# include <sys/event.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <fcntl.h>
# include <unistd.h>
# include <cstdlib>
# include <iostream>
# include <map>
# include <string>
# include <vector>
# include <sstream>
# include <ctime>

# include "../Client/Client.class.hpp"
# include "../Channel/Channel.class.hpp"
# include "../Message/Message.class.hpp"

// forward declarations
std::string generateResponse(std::string prefix, std::string code, std::vector<std::string> params, std::string msg);
class Channel;
class Client;

class Server {
  public:
    // function pointer for the functionMap
    typedef std::string (Server::*fctPointer)(Client * client, Message & msg);

    Server(void);
    Server(Server const & src);
    Server(std::string port, std::string pass);
    ~Server(void);

    // Registration
    void registerClient(Client * client);

    // Checkers
    bool channelExists(std::string const name) const;
    bool clientRegistered(int socket) const;
    bool informationValid(Client * client) const;

    // Getters
    Client * getClientBySocket(int socket);
    Client * getClientByName(std::string name);
    Channel * getChannel(std::string & name);

    // Setters
    void addChannel(Channel * channel);
    void addClient(Client * client);
    void removeChannel(Channel * channel);
    void removeClient(Client * client);

    // Server setup
    int makeServerSocket(void);
    int setUpKQ(void);
    void start(void);

    // Parsing
    std::vector<Message> parse(std::string input);
    void handlePartialReq(char buffer[512]);

    // Message handling
    std::string execute(Client * client, Message & msg);
    void handleRequest(int socket, std::string buffer);
    std::map<std::string, fctPointer> getFunctionMap(void);

    // Commands (found in ./Commands/*.cpp)
    std::string pass(Client * client, Message & msg);
    std::string nick(Client * client, Message & msg);
    std::string user(Client * client, Message & msg);
    std::string quit(Client * client, Message & msg);
    std::string join(Client * client, Message & msg);
    std::string part(Client * client, Message & msg);
    std::string privmsg(Client * client, Message & msg);
    std::string pong(Client * client, Message & msg);
    std::string who(Client * client, Message & msg);
    std::string mode(Client * client, Message & msg);
    std::string die(Client * client, Message & msg);
    
    //oper
    std::string oper(Client * client, Message & msg);
    std::string kick(Client * client, Message & msg);
    std::string topic(Client * client, Message & msg);


    // Overloads
    Server & operator=(Server const & rhs);
  private:
    std::string _port;
    std::string _password;
    std::string _opepass;
    int _server_socket;
    int _kq;
    struct kevent _event;
    std::vector<Client *> _userbase;
    std::vector<Channel*> _channels;
    std::string _line;
};

std::ostream & operator<<(std::ostream & o, Server const & i);

#endif // SERVERCLASS_H_
