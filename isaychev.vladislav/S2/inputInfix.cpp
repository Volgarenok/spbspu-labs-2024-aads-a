#include "inputInfix.hpp"
#include <iostream>
#include <cctype>

void isaychev::inputInfix(std::istream & in, Queue< char > & infExp)
{
  in >> std::noskipws;
  char c = 0;
  while (in >> c)
  {
    if (c == ' ')
    {
      continue;
    }
    else if (c == '(' || c == ')')
    {
      infExp.push(c);
    }
    else if (c == '+' || c == '-')
    {
      infExp.push(c);
    }
    else if (c == '/' || c == '*' || c == '%')
    {
      infExp.push(c);
    }
    else if (std::isdigit(c))
    {
      infExp.push(c);
    }
    else if (c == '\n')
    {
      break;
    }
  }
  in >> std::skipws;
}
