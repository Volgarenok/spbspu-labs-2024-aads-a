#ifndef STACK_TYPE_HPP
#define STACK_TYPE_HPP

#include "expression_types.hpp"

namespace nikitov
{
  struct StackType
  {
  public:
    StackType() = default;
    explicit StackType(bool value);
    explicit StackType(char value);

    bool isOpenBracket() const;
    bool isCloseBracket() const;
    char getOperation() const;
    ExprTypeName getType() const;

  private:
    union
    {
      detail::Bracket bracket;
      detail::Operation operation;
    };
    ExprTypeName type;
  };
}
#endif
