#include "tokens.hpp"
#include <cstddef>
#include <stdexcept>

bool sakovskaia::isOperator(const std::string & token)
{
  return token == "+" || token == "-" || token == "*" || token == "/" || token == "%";
}

bool sakovskaia::isOperand(const std::string & token)
{
  return !isOperator(token) && token != "(" && token != ")";
}
