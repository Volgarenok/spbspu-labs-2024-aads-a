#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include <cstddef>
#include "queue.hpp"

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
    TokenType getType() const noexcept;
    TokenType& getType() noexcept;
    Operand getOperand() const noexcept;
    Operand& getOperand() noexcept;
    Operation getOp() const noexcept;
    Operation& getOp() noexcept;
    Bracket getBracket() const noexcept;
    Bracket& getBracket() noexcept;
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
    Postfix() = default;
    Postfix(InfixType&& inf);
    Postfix(TokenType inType, Operation inOperation);
    Postfix convertToPostfix(const InfixType& inf);
    TokenType getPostix() const noexcept;
    Operand getOperand() const noexcept;
    Operation getOperation() const noexcept;
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
