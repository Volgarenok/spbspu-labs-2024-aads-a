#ifndef TOKEN_HPP
#define TOKEN_HPP
#include "types.hpp"

namespace strelyaev
{
  enum class typeOfExpression
  {
    OPERAND = 0,
    OPERATION = 1,
    BRACKET = 2
  };

  union Token
  {
    Token() = delete;
    Token(long long);
    Token(char);
    
    Operand operand;
    Operation operation;
    Bracket bracket;
  };

  struct infixUnit
  {
    infixUnit() = delete;
    Token token;
    typeOfExpression type;
  };
}

#endif
