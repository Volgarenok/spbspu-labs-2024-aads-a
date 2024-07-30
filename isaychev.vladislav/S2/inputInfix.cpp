#include "inputInfix.hpp"
#include <string>
#include <iostream>
#include <cctype>
#include <stdexcept>

void isaychev::inputInfix(std::istream & in, Queue< Token > & infExp)
{
  std::string str = "";
  std::getline(in, str);
  if (str.empty())
  {
    throw std::length_error("empty string");
  }

  for (size_t i = 0; i < str.length(); ++i)
  {
    if (str[i] == ' ')
    {
      continue;
    }
    else if (str[i] == '(')
    {
      infExp.push(Token(BracketType::OPENING));
    }
    else if (str[i] == ')')
    {
      infExp.push(Token(BracketType::CLOSING));
    }
    else if (std::isdigit(str[i]))
    {
      std::string num = "";
      do
      {
        num += str[i];
        ++i;
      }
      while (str[i] != ' ' && std::isdigit(str[i]) && i < str.length());
      infExp.push(Token(std::stoll(num, nullptr, 10)));
    }
    else
    {
      infExp.push(Token(str[i]));
    }
  }
}
