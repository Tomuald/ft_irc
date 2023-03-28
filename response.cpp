#include <string>
#include <sstream>
#include <vector>
#include "Client/Client.class.hpp"

std::string generateResponse(std::string prefix, std::string code, std::vector<std::string> params, std::string msg) {
  std::stringstream response;
  if (!prefix.empty())
    response << ":" + prefix << " ";
  if (!code.empty())
    response << code << " ";

  std::vector<std::string>::iterator it;
  for (it = params.begin(); it != params.end(); ++it) {
    std::vector<std::string>::iterator next_it = it;
    std::advance(next_it, 1);
    response << *it;
    if (next_it != params.end()) {
      response << " ";
    }
  }
  if (!msg.empty())
    response << " :" << msg;
  response << "\r\n";
  return (response.str());
}
