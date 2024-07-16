#include "inputInfix.hpp"
#include <string>
#include <iostream>
#include <cctype>
#include <stdexcept>

bool isOper(char c)
{
  return c == '+'|| c == '-' || c == '%' || c == '/' || c == '*';
}

bool isBracket(char c)
{
  return c == '(' || c == ')';
}

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
    Token token;

    if (str[i] == ' ')
    {
      continue;
    }
    else if (isBracket(str[i]))
    {
      token.value.bracket.set_type(str[i]);
      token.type = TokenType::BRACKET;
      infExp.push(token);
    }
    else if (isOper(str[i]))
    {
      token.value.operation.set_operation(str[i]);
      token.type = TokenType::OPERATION;
      infExp.push(token);
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
      token.value.operand.set_operand(std::stoll(num, nullptr, 10));
      token.type = TokenType::OPERAND;
      infExp.push(token);
    }
    else
    {
      throw std::invalid_argument("wrong token");
    }
  }
}
