#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include <cstddef>
#include "basicTypes.hpp"

namespace novokhatskiy
{
  struct InfixType
  {
    TokenType type;
    union
    {
      Operand operand;
      Operation operation;
      Bracket bracket;
    };
  };

  struct Postfix
  {
    TokenType type;
    union
    {
      Operand operand;
      Operation operation;
    };
    Postfix() = default;
    Postfix(InfixType&& inf);
    Postfix(TokenType inType, Operation inOperation);
    Postfix convertToPostfix(const InfixType& inf);
  };
}

#endif

