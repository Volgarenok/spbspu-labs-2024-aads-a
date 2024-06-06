#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include <cstddef>
#include <queue.hpp>

namespace novokhatskiy
{
  enum class TokenType
  {
    OPERATION,
    OPERAND,
    BRACKET,
  };

  struct Bracket
  {
    bool isOpen;
    Bracket() = default;
    Bracket(bool val);
  };

  struct Operand
  {
    long long num;
    Operand() = default;
    Operand(long long val);
  };

  struct Operation
  {
    char operation;
    Operation() = default;
    Operation(char val);
  };

  class InfixType
  {
  public:
    InfixType() = default;
    explicit InfixType(long long val);
    static InfixType openBracket();
    static InfixType closeBracket();
    explicit InfixType(char val);
    bool isOpenBracket() const;
    bool isCloseBracket() const;
    TokenType getType() const noexcept;
    Operand getOperand() const noexcept;
    Operation getOp() const noexcept;
    Bracket getBracket() const noexcept;

  private:
    union
    {
      Operand operand;
      Operation operation;
      Bracket bracket;
    };
    TokenType type;
    explicit InfixType(bool val);
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
