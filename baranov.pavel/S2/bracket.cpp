#include "bracket.hpp"
#include <stdexcept>

baranov::Bracket::Bracket(char c)
{
  if (c == '(')
  {
    type_ = BracketType::OPEN;
  }
  else if (c == ')')
  {
    type_ = BracketType::CLOSE;
  }
  else
  {
    throw std::logic_error("Invalid bracket sign");
  }
}

baranov::BracketType baranov::Bracket::getType() const
{
  return type_;
}

