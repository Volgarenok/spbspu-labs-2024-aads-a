#include "inputInfix.hpp"
#include <iostream>
#include <cctype>
#include <stdexcept>

void isaychev::inputInfix(std::istream & in, Queue< std::string > & infExp)
{
  std::string str = "";
  std::getline(in, str, '\n');
  for (auto i = str.begin(); i != str.end(); ++i)
  {
    std::string token = "";
    if (*i == ' ')
    {
      continue;
    }
    else if (*i == '(' || *i == ')')
    {
      token += *i;
      infExp.push(token);
    }
    else if (*i == '+' || *i == '-')
    {
      token += *i;
      infExp.push(token);
    }
    else if (*i == '/' || *i == '*' || *i == '%')
    {
      token += *i;
      infExp.push(token);
    }
    else if (std::isdigit(*i))
    {
      token += *(i++);
      while (*i != ' ' && std::isdigit(*i) && i != str.end())
      {
        token += *i;
        ++i;
      }
      infExp.push(token);
    }
    else
    {
      throw std::invalid_argument("wrong token");
    }
  }
}
