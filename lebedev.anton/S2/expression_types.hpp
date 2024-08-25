#ifndef EXPRESSION_TYPES_HPP
#define EXPRESSION_TYPES_HPP

#include "symbols.hpp"

namespace lebedev
{
  struct InfixExpression
  {
  public:
    InfixExpression() = default;
    explicit InfixExpression(long long value);
    explicit InfixExpression(char value);
    explicit InfixExpression(bool value);

    bool isOpenBracket() const;
    bool isCloseBracket() const;

    Symbol getType() const;
    bool getBracket() const;
    char getOperation() const;
    long long getOperand() const;
  private:
    union
    {
      Bracket bracket;
      Operation operation;
      Operand operand;
    };
    Symbol symbol;
  };

  struct PostfixExpression
  {
  public:
    PostfixExpression() = default;
    explicit PostfixExpression(long long value);
    explicit PostfixExpression(char value);

    Symbol getType() const;
    char getOperation() const;
    long long getOperand() const;
  private:
    union
    {
      Operation operation;
      Operand operand;
    };
    Symbol symbol;
  };
}

#endif
