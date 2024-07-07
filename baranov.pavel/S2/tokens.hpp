#ifndef TOKENS_HPP
#define TOKENS_HPP

#include <stdexcept>
#include <string>

namespace baranov
{
  enum class OperationType
  {
    ADDITION,
    SUBTRACTION,
    MULTIPLICATION,
    DIVISION,
    MODULATION
  };

  struct Operation
  {
    OperationType type;
    unsigned char priority;
  };

  struct Operand
  {
    long long int value;
  };

  enum class BracketType
  {
    OPEN,
    CLOSE
  };

  struct Bracket
  {
    BracketType type;
  };

  enum class TokenType
  {
    OPERATION,
    OPERAND,
    BRACKET
  };

  union TokenValue
  {
    Operation operation;
    Operand operand;
    Bracket bracket;
  };

  struct Token
  {
    TokenType type;
    TokenValue value;

    Token(const std::string & str);
  };
}

#endif

