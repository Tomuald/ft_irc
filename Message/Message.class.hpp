#ifndef MESSAGE_CLASS_HPP_
# define MESSAGE_CLASS_HPP_

# include <iostream>
# include <string>
# include <map>
# include <vector>

class Message {
public:
  Message(void);
  Message(Message const & src);
  Message(const std::string & line);
  ~Message(void);

  Message& operator=(Message const & rhs);

  std::vector<std::string> & getParams(void);

  std::string prefix;
  std::string command;
  std::vector<std::string> params;
private:
};

std::ostream & operator<<(std::ostream & o, Message const & i);
#endif // MESSAGE_CLASS_HPP_
