#ifndef GET_POSTFIX_FORM_HPP
#define GET_POSTFIX_FORM_HPP

#include <iosfwd>
#include <string>
#include "queue.hpp"

namespace marishin
{
  void getPostfixForm(std::istream& in, Queue< std::string >& queue);
  void getFromStack(Stack<std::string> &stack, std::string &value);
  std::string& getPostfixFormIn(std::istream& in, std::string& result);
  bool binary(const std::string& p);
  bool priority(const std::string& stack, const std::string& current);
  void operations(Stack<std::string> &stack, const std::string &str, std::string &value);
}

#endif
