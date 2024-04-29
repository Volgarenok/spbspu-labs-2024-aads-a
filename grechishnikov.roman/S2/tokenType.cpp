#include "tokenType.hpp"
#include <cstddef>
#include <stdexcept>

bool grechishnikov::isOperator(const std::string& token)
{
  return token == "+" || token == "-" || token == "*" || token == "/" || token == "%";
}

bool grechishnikov::isOperand(const std::string& token)
{
  size_t count = 0;
  try
  {
    std::stoll(token, &count);
  }
  catch(...)
  {
    return 0;
  }
  return count == token.size();
}
