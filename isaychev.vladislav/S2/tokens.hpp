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
    explicit Bracket(char c)
    {
      set_type(c);
    }

    void set_type(char c)
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

    BracketType get_type()
    {
      return type_;
    }

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

    TokenUnit(long long int):
     operand(0)
    {}
  };

  struct Token
  {
    TokenUnit value;
    TokenType type;

    Token():
     value(0),
     type(TokenType::UNKNOWN)
    {}
  };
}

#endif
