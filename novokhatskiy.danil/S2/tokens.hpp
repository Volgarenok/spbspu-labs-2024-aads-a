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
  
  struct Operand
  {
    Operand() = default;
    Operand(long long value);
    long long value;
  };

  struct Operation
  {
    Operation() = default;
    Operation(char value);
    bool operator<(const Operation& other) const;
    char operation;
  };

  struct Bracket
  {
    Bracket() = default;
    Bracket(char32_t bracket);
    char32_t scope;
  };
  union Expression
  {
    Expression() = default;
    Expression(long long data);
    Expression(PartsOfExpression type, char data);
    Operand operand;
    Bracket bracket;
    Operation operation;
    PartsOfExpression type;
  };

  struct InfixType
  {
    InfixType() = default;
    InfixType(PartsOfExpression type, long long data);
    InfixType(PartsOfExpression type, char data);
    Expression data;
    PartsOfExpression type;
  };

  struct Postfix
  {
    union postfix_t
    {
      Operand operand;
      Operation operation;
      postfix_t(long long value);
      postfix_t(char value);
      postfix_t(InfixType& inf);
    };
    Postfix() = default;
    Postfix(PartsOfExpression type, long long data);
    Postfix(PartsOfExpression type, char data);
    postfix_t data;
    PartsOfExpression type;
  }; 
}

#endif
