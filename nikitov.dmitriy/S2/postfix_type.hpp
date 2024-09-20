#ifndef POSTFIX_TYPE_HPP
#define POSTFIX_TYPE_HPP

#include "expression_types.hpp"

namespace nikitov
{
  struct PostfixType
  {
  public:
    PostfixType() = default;
    explicit PostfixType(long long value);
    explicit PostfixType(char value);

    long long getOperand() const;
    char getOperation() const;
    ExprTypeName getType() const;

  private:
    union
    {
      detail::Operand operand;
      detail::Operation operation;
    };
    ExprTypeName type;
  };
}
#endif
