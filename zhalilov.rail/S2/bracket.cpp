#include "bracket.hpp"

zhalilov::Bracket::Bracket(Type type):
  type_(type)
{}

zhalilov::Bracket::Type zhalilov::Bracket::getBracketType() const
{
  return type_;
}
