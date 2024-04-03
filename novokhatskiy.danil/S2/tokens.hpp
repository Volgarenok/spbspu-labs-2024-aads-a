#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include <cstddef>

namespace novokhatskiy
{
  enum class PartsOfExpression
  {
    operand = 0,
    operation = 1,
    bracket = 2
  };
  
  struct Operand
  {
    Operand() = default;
    size_t value_;
  };

  struct Operation
  {
    Operation() = default;
    bool operator<(const Operation& other) const;
    char operation_;
  };

  struct Bracket
  {
  public:
    Bracket() = default;
    char scope;
  };
  union Expression
  {
    Expression() = default;
    Operand operand;
    Bracket bracket;
    Operation operation;
  };

  struct InfixType
  {
    InfixType() = default;
    Expression data_;
    PartsOfExpression type_;
  };

  struct Postfix
  {
    union postfix_t
    {
      Operand operand;
      Operation operation;
    };
    postfix_t data_;
    PartsOfExpression type_;
  };  
}

#endif
