#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include <cstddef>

namespace novokhatskiy
{
  enum class PartsOfExpression
  {
    OPERAND = 0,
    OPERATION = 1,
    BRACKET = 2
  };

  enum class PriorityOfOperation
  {
    plus = 1,
    minus = 1
  };

  struct Operand
  {
    long long value;
    Operand() = default;
  };

  struct Operation
  {
    char operation;
    Operation() = default;
    bool operator<(const Operation &other) const;
  };

  struct Bracket
  {
    Bracket() = default;
    char scope;
  };

  struct InfixType
  {
    union infix_t
    {
      Operand operand;
      Operation operation;
      Bracket bracket;
    };
    infix_t data;
    PartsOfExpression type;
    InfixType() = default;
    void print();
    size_t getPriority();
  };

  struct Postfix
  {
    union postfix_t
    {
      Operand operand;
      Operation operation;
    };
    postfix_t data;
    PartsOfExpression type;
    Postfix() = default;
    Postfix convertToPostfix(const InfixType &inf);
  };
}

#endif
