#include "calculations.hpp"
#include <stdexcept>
#include <iostream>

bool strelyaev::isOperation(std::string& c)
{
  return ((c == "+") || (c == "-") || (c == "/") || (c == "*") || (c == "%"));
}

bool strelyaev::isBracket(std::string& c)
{
  return ((c == "(") || (c == ")"));
}

int strelyaev::getPrecedence(char c)
{
  if (c == '+' || c == '-')
  {
    return 1;
  }
  if (c == '*' || c == '%' || c == '/')
  {
    return 2;
  }
  if (c == '(' || c == ')')
  {
    return 0;
  }
  return -1;
}

long long strelyaev::calculateOperation(long long first, long long second, char operation)
{
  switch (operation)
  {
  case '+':
    return first + second;
  case '-':
    return first - second;
  case '*':
    return first * second;
  case '/':
    return first / second;
  case '%':
    return first % second;
  }
  throw std::logic_error("Invalid operation");
}

