#ifndef TOKENS_HPP
#define TOKENS_HPP

#include <stdexcept>
#include "binOper.hpp"

namespace isaychev
{
  enum class BracketType
  {
    OPENING,
    CLOSING
  };

  class Bracket
  {
   public:
    explicit Bracket(char c);

    void set_type(char c);
    BracketType get_type();

   private:
    BracketType type_;
  };

  enum class TokenType
  {
    OPERATION,
    BRACKET,
    OPERAND,
    UNKNOWN
  };

  union TokenUnit
  {
    Operand operand;
    Operation operation;
    Bracket bracket;

    TokenUnit(long long int);
  };

  struct Token
  {
    TokenUnit value;
    TokenType type;

    Token();
  };
}

#endif
