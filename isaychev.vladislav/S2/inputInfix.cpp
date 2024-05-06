#include "inputInfix.hpp"
#include <iostream>
#include <cctype>
#include <stdexcept>

bool isOper(const char c)
{
  return c == '+'|| c == '-' || c == '%' || c == '/' || c == '*';
}

bool isBracket(const char c)
{
  return c == '(' || c == ')';
}

void isaychev::inputInfix(std::istream & in, Queue< std::string > & infExp)
{
  std::string str = "";
  std::getline(in, str);
  if (str.empty())
  {
    throw std::length_error("empty string");
  }
  std::string token;
  for (size_t i = 0; i < str.length(); ++i)
  {
    token = "";
    if (str[i] == ' ')
    {
      continue;
    }
    else if (isBracket(str[i]))
    {
      token += str[i];
      infExp.push(token);
    }
    else if (isOper(str[i]))
    {
      token += str[i];
      infExp.push(token);
    }
    else if (std::isdigit(str[i]))
    {
      do
      {
        token += str[i];
        ++i;
      }
      while (str[i] != ' ' && std::isdigit(str[i]) && i < str.length());
      infExp.push(token);
    }
    else
    {
      throw std::invalid_argument("wrong token");
    }
  }
}
