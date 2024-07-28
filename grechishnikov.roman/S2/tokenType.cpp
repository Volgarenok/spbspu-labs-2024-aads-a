#include "tokenType.hpp"
#include <cstddef>
#include <stdexcept>

bool grechishnikov::isOperator(const std::string& token)
{
  return token == "+" || token == "-" || token == "*" || token == "/" || token == "%";
}

bool grechishnikov::isOperand(const std::string& token)
{
  return !isOperator(token) && token != "(" && token != ")";
}
