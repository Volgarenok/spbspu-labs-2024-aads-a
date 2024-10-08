#ifndef OUTPUT_HPP
#define OUTPUT_HPP

#include "queue.hpp"
#include <string>
namespace vojuck
{
  int precedence(const std::string& op);
  bool isOperator(const std::string& token);
  int evaluatePostfix(const Queue<std::string>& postfixQueue);
  Queue<std::string> infixToPostfix(const std::string& expression);
}

#endif
