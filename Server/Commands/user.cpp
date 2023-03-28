#include "../Server.class.hpp"

std::string Server::user(Client & client, Message & msg) {
  std::vector<std::string> null_vector(0);
  if (msg.params.size() < 4)
    return (generateResponse("ft_irc", "461", null_vector, "Not enough parameters"));

  if (client.isRegistered() == true) {
    return (generateResponse("ft_irc", "462", null_vector, "You may not reregister"));
  }
  client.setUsername(msg.params[0]);

  size_t i;
  std::string real_name;
  for (i = 3; i < msg.params.size(); i++)
    real_name.append(msg.params[i]);
  client.setRealname(real_name);
  client.setIP(msg.params[2]);
  return ("User information set\r\n");
}
