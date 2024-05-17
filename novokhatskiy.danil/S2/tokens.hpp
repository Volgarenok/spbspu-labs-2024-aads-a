#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include <cstddef>
#include "queue.hpp"
#include "calculate_expression.hpp"

namespace novokhatskiy
{
  enum class TokenType
  {
    OPERATION,
    OPERAND,
    BRACKET,
  };

  struct Operand
  {
    long long num;
  };

  enum class Operation
  {
    ADD = '+',
    SUB = '-',
    MUL = '*',
    DIV = '/',
    MOD = '%',
  };

  enum class Bracket
  {
    OPEN = '(',
    CLOSE = ')',
  };

  class InfixType
  {
  public:
    TokenType getInfix() const noexcept;
    friend void inputInfix(Queue<Queue<InfixType>> &infixQueue, std::istream &in);

  private:
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
    TokenType getPostix() noexcept;
    Postfix() = default;
    Postfix(InfixType &&inf);
    Postfix(TokenType inType, Operation inOperation);
    Postfix convertToPostfix(const InfixType &inf);
    char getOperation() const noexcept;

  private:
    TokenType type;
    union
    {
      Operand operand;
      Operation operation;
    };
  };
}

#endif
