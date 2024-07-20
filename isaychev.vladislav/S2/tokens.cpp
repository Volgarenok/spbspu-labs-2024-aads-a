#include "tokens.hpp"

isaychev::Bracket::Bracket(char c):
 type_(BracketType::OPENING)
{
  if (c == ')')
  {
    type_ = BracketType::CLOSING;
  }
  else if (c != '(')
  {
    throw std::logic_error("not a bracket");
  }
}

isaychev::Bracket::Bracket(BracketType type):
 type_(type)
{}

isaychev::BracketType isaychev::Bracket::get_type() const noexcept
{
  return type_;
}

isaychev::TokenUnit::TokenUnit(long long int n):
 operand(n)
{}

isaychev::TokenUnit::TokenUnit(char c):
 operation(c)
{}

isaychev::TokenUnit::TokenUnit(BracketType type):
 bracket(type)
{}

isaychev::Token::Token(long long int n):
 value(n),
 type(isaychev::TokenType::OPERAND)
{}

isaychev::Token::Token(char c):
 value(c),
 type(isaychev::TokenType::OPERATION)
{
  if (value.operation.get_type() == OperationType::UNKNOWN)
  {
    type = TokenType::UNKNOWN;
  }
}

isaychev::Token::Token(BracketType type):
 value(type),
 type(isaychev::TokenType::BRACKET)
{}
