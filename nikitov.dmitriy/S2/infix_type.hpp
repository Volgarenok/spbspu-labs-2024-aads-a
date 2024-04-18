#ifndef INFIX_TYPE_HPP
#define INFIX_TYPE_HPP

#include "expression_types.hpp"

namespace nikitov
{
  struct InfixType
  {
  public:
    InfixType() = default;
    explicit InfixType(long long value);
    explicit InfixType(char value);

    static InfixType openBracket();
    static InfixType closeBracket();

    bool isOpenBracket() const;
    bool isCloseBracket() const;
    long long getOperand() const;
    char getOperation() const;
    ExprTypeName getType() const;

  private:
    union
    {
      detail::Bracket bracket;
      detail::Operand operand;
      detail::Operation operation;
    };
    ExprTypeName type;

    explicit InfixType(bool value);
  };
}
#endif
