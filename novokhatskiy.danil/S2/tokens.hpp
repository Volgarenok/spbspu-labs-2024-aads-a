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
    friend class Postfix;
    friend void inputInfix(Queue<Queue<InfixType>>& infixQueue, std::istream& in);
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
    friend class InfixType;
    friend long long calculatePostExp(Queue< Postfix >&& inQueue);
    friend Queue<Postfix> convertExpression(Queue<InfixType>&& infixQueue);
    Postfix() = default;
    Postfix(InfixType&& inf);
    Postfix(TokenType inType, Operation inOperation);
    Postfix convertToPostfix(const InfixType& inf);
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
