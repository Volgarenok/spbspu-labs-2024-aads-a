#include "checks.hpp"

bool ishmuratov::isOperator(const std::string &opr)
{
  return opr == "+" || opr == "-" || opr == "*" || opr == "/" || opr == "%";
}

bool ishmuratov::high_priority(const std::string& opr)
{
  return (opr == "*" || opr == "/" || opr == "%");
}

bool ishmuratov::low_priority(const std::string& opr)
{
  return (high_priority(opr) || (opr == "+") || (opr == "-"));
}