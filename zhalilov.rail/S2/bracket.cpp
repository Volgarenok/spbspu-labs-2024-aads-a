#include "bracket.hpp"

zhalilov::Bracket::Bracket(Type type):
  type_(type)
{}

zhalilov::PrimaryType zhalilov::Bracket::getPrimaryType() const
{
  return PrimaryType::Bracket;
}

zhalilov::Bracket::Type zhalilov::Bracket::getBracketType() const
{
  return type_;
}
