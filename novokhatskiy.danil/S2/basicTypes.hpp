#ifndef BASIC_TYPES_HPP
#define BASIC_TYPES_HPP

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
}

#endif
