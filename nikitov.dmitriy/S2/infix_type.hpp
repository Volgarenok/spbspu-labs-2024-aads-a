#ifndef INFIX_TYPE_HPP
#define INFIX_TYPE_HPP

#include "expression_types.hpp"

namespace nikitov
{
  struct InfixType
  {
  public:
    InfixType() = default;
    explicit InfixType(bool value);
    explicit InfixType(long long value);
    explicit InfixType(char value);

    bool& getBracket();
    long long& getOperand();
    char& getOperation();
    ExprTypeName getType() const;

  private:
    union
    {
      detail::Bracket bracket;
      detail::Operand operand;
      detail::Operation operation;
    };
    ExprTypeName type;
  };
}
#endif
