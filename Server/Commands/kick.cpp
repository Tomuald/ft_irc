#include "../Server.class.hpp"

/**
    * @brief 

    Command: KICK
    Parameters: <channel> <user> [<comment>]

    Eje:
    KICK #Finnish John :Speaking English
                                ; Kick John from #Finnish using
                                "Speaking English" as the reason
                                (comment).
*/

std::string Server::kick(Client * client, Message & msg) {
    std::vector<std::string> params;
    std::string response;

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

    /**
    * @brief kick user
    */
    std::vector<Client *>::iterator it;
    Client *tmp = this->getClientByName(msg.params[1]);
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

    // Notify the channel kick user
    params.push_back("KICK");
    params.push_back(msg.params[0]);
    params.push_back(msg.params[1]);
    response = generateResponse(client->getIdentifier(), "", params, "");
    Channel *chtmp = this->getChannel(msg.params[0]);
    std::vector<Client *> clients = chtmp->getClients();
    for (it = clients.begin(); it != clients.end(); ++it) {
        send((*it)->getSocket(), response.c_str(), response.length(), 0);
    }
  
  return ("");
}
