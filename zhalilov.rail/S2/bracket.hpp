#ifndef BRACKET_HPP
#define BRACKET_HPP

#include "primaryType.hpp"

namespace zhalilov
{
  class Bracket
  {
  public:
    enum class Type
    {
      OpenBracket,
      CloseBracket
    };

    explicit Bracket(Type);
    Type getBracketType() const;

  private:
    Type type_;
  };
}

#endif
