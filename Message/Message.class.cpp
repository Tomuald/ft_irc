#include "Message.class.hpp"

Message::Message(void) { return ; }

Message::Message(Message const & src) {
  this->prefix = src.prefix;
  this->command = src.command;
  this->params = src.params;
  return ;
}

Message::Message(const std::string& line) {
  std::string trimmed_line = line;
  trimmed_line.erase(trimmed_line.find_last_not_of(" \n\r\t")+1); // trim whitespace

  std::string::size_type pos = 0;
  if (trimmed_line[pos] == ':') {
    std::string::size_type prefix_end = trimmed_line.find(' ', pos);
    if (prefix_end != std::string::npos) {
      this->prefix = trimmed_line.substr(pos + 1, prefix_end - pos - 1);
      pos = prefix_end + 1;
    }
  }

  std::string::size_type cmd_end = trimmed_line.find(' ', pos);
  if (cmd_end != std::string::npos) {
    this->command = trimmed_line.substr(pos, cmd_end - pos);
    pos = cmd_end + 1;
  }

  while (pos < trimmed_line.length()) {
    std::string param;
    if (trimmed_line[pos] == ':') {
      param = trimmed_line.substr(pos + 1);
      this->params.push_back(param);
      break;
    } else {
      std::string::size_type param_end = trimmed_line.find(' ', pos);
      if (param_end != std::string::npos) {
        param = trimmed_line.substr(pos, param_end - pos);
        param.erase(param.find_last_not_of(" \n\r\t")+1); // trim whitespace
        this->params.push_back(param);
        pos = param_end + 1;
      } else {
        param = trimmed_line.substr(pos);
        param.erase(param.find_last_not_of(" \n\r\t")+1); // trim whitespace
        this->params.push_back(param);
        break;
      }
    }
  }
  if (this->command.empty() && !this->params.empty()) {
    this->command = this->params[0];
    this->params.erase(this->params.begin());
  }
}

std::vector<std::string> & Message::getParams(void) {
  return (this->params);
}

Message::~Message(void) { return ; }

Message & Message::operator=(Message const & rhs) {
  if (this != &rhs) {
    this->prefix = rhs.prefix;
    this->command = rhs.command;
    this->params = rhs.params;
  }
  return (*this);
}

std::ostream & operator<<(std::ostream & o, Message const & i) {
  o << i.command;
  (void) i;
  return (o);
}
