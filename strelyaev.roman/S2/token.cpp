#include "token.hpp"

strelyaev::Token::Token(long long value):
  operand(value)
{}

strelyaev::Token::Token(char value):
  operand(0)
{
  if (value == '(' || value == ')')
  {
    bracket = value;
  }
  else
  {
    operation = value;
  }
}


