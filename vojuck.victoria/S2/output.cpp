#include "output.hpp"

bool vojuck::isOperator(const std::string& token)
{
  return token == "+" || token == "-" || token == "*" || token == "/" || token == "%";
}
