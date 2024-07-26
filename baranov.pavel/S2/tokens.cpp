#include "tokens.hpp"

baranov::Token::Token(const std::string & str)
{
  char c = str[0];
  if (c == '(' || c == ')')
  {
    type_ = TokenType::BRACKET;
    value_.bracket = Bracket(c);
  }
  else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%')
  {
    type_ = TokenType::OPERATION;
    value_.operation = Operation(c);
  }
  else
  {
    type_ = TokenType::OPERAND;
    value_.operand = Operand(std::stoull(str));
  }
}

baranov::Token::Token(long long int num)
{
  type_ = TokenType::OPERAND;
  value_.operand = Operand(num);
}

baranov::TokenType baranov::Token::getType() const
{
  return type_;
}

baranov::TokenValue baranov::Token::getValue() const
{
  return value_;
}

