#include "tokenType.hpp"
#include <cstddef>

bool grechishnikov::isOperator(const std::string& token)
{
  return token == "+" || token == "-" || token == "*" || token == "/" || token == "%";
}

bool grechishnikov::isOperand(const std::string& token)
{
  size_t count = 0;
  std::stoll(token, &count);
  return count == token.size();
}
