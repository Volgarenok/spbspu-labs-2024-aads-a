#include "operations.hpp"

bool chernov::isOperation(const std::string& elem)
{
  return elem == "+" || elem == "-" || elem == "*" || elem == "/" || elem == "%";
}

bool chernov::priority(const std::string& top, const std::string& curr)
{
  return ((top == "*" || top == "/" || top == "%") || ((top == "+" || top == "-") && (curr == "+" || curr == "-")) ? true : false);
}
