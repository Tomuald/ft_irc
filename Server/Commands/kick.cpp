#include "../Server.class.hpp"

/**
    Command: KICK
    Parameters: <channel> <user> [<comment>]

    KICK &Melbourne Matthew         ; Kick Matthew from &Melbourne

    KICK #Finnish John :Speaking English
                                ; Kick John from #Finnish using
                                "Speaking English" as the reason
                                (comment).
*/

std::string Server::kick(Client * client, Message & msg) {
    std::vector<std::string> params;

    std::cout << "Params = " << msg.params.size() << std::endl;
    std::cout << "Params_01 = " << msg.params[1] << std::endl;

    if (msg.params.size() < 2) {
        params.push_back(client->getNickname());
        params.push_back(client->getMode());
        return (generateResponse("ft_irc", "461", params, "Not enough parameters"));
    }
    if (client->getNickname() != "@Oper42") {
        params.push_back(client->getNickname());
        params.push_back(client->getMode());
        return (generateResponse("ft_irc", "482", params, "You're not channel operator"));
    }
    ;
    if (this->channelExists(msg.params[0]) == false) {
        params.push_back(msg.params[0]);
        return (generateResponse("ft_irc", "403", params, "No such channel"));
    }
    if (this->getClientByName(msg.params[1]) == false) {
        params.push_back(msg.params[0]);
        return (generateResponse("ft_irc", "442", params, "User not on that channel"));
    }

    std::cout << "Server had: " << this->_userbase.size() << " users" << std::endl;
    std::vector<Client *>::iterator it;
    Client *tmp = this->getClientByName(msg.params[1]);
    if (tmp != nullptr)
        std::cout << "Client_NICK = " << tmp->getNickname() << std::endl;
    for (it = this->_userbase.begin(); it != this->_userbase.end(); ) {
        if ((*it)->getNickname() == tmp->getNickname()) {
            std::cout << tmp->getNickname() << " user kick !!" << std::endl;
            close(tmp->getSocket());
            delete (*it);
            it = this->_userbase.erase(it);
            
        } else {
            ++it;
        }
    }
    std::cout << "Server now has: " << this->_userbase.size() << " users" << std::endl;
  
  return ("");
}
