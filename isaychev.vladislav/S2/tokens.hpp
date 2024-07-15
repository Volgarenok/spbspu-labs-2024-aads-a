#ifndef TOKENS_HPP
#define TOKENS_HPP

#include <stdexcept>
#include "binOper.hpp"

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

  class Bracket
  {
   public:
    explicit Bracket(char c)
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

   private:
    BracketType type_;
  };

  union Token
  {
    Operand operand;
    Operation operation;
    Bracket bracket;
  };

  struct TokenUnit
  {
    Token tok;
    TokenType type;
  };
}

#endif
