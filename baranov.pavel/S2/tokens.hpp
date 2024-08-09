
#ifndef TOKENS_HPP
#define TOKENS_HPP

#include <stdexcept>
#include <string>
#include "bracket.hpp"
#include "operand.hpp"
#include "operation.hpp"

namespace baranov
{
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

  class Token
  {
  public:
    explicit Token(const std::string & str);
    explicit Token(long long int num);
    TokenType getType() const;
    TokenValue getValue() const;
  private:
    TokenType type_;
    TokenValue value_;
  };
}

#endif

