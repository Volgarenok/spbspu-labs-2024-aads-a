#include "utilities.hpp"

bool isNum(char c)
{
  return (c >= '0' && c <= '9');
}

bool isOperator(char c)
{
  return (c == '+' || c == '-' || c == '*' || c == '/');
}

int getPriority(char op)
{
  if (op == '*' || op == '/')
  {
    return 2;
  }
  else if (op == '+' || op == '-')
  {
    return 1;
  }
  else
  {
    return 0;
  }
}
