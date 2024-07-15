#ifndef TOKENS_HPP
#define TOKENS_HPP

namespace isaychev
{
  enum class TokenType
  {
    OPERATION,
    BRACKET,
    OPERAND,
    UNKNOWN
  };

  enum class BracketType
  {
    OPENING,
    CLOSING
  };
}

#endif
