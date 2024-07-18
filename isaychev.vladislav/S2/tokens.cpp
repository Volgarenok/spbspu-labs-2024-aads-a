#include "tokens.hpp"

isaychev::Bracket::Bracket(char c)
{
  set_type(c);
}

void isaychev::Bracket::set_type(char c)
{
  if (c == '(')
  {
    type_ = BracketType::OPENING;
  }
  else if (c == ')')
  {
    type_ = BracketType::CLOSING;
  }
  else
  {
    throw std::logic_error("not a bracket");
  }
}

isaychev::BracketType isaychev::Bracket::get_type()
{
  return type_;
}

isaychev::TokenUnit::TokenUnit(long long int):
 operand(0)
{}

isaychev::Token::Token():
 value(0),
 type(isaychev::TokenType::UNKNOWN)
{}
