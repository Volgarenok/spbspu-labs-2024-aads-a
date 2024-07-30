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
    explicit Bracket(BracketType type);

    BracketType get_type() const noexcept;

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
    TokenUnit(char c);
    TokenUnit(BracketType type);
  };

  struct Token
  {
    TokenUnit value;
    TokenType type;

    explicit Token(long long n);
    explicit Token(char c);
    explicit Token(BracketType type);
  };
}

#endif
