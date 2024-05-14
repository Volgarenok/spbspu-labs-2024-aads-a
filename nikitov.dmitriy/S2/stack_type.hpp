#ifndef STACK_TYPE_HPP
#define STACK_TYPE_HPP

#include "expression_types.hpp"

namespace nikitov
{
  struct StackType
  {
  public:
    StackType() = default;
    explicit StackType(char value);

    static StackType openBracket();
    static StackType closeBracket();

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

    explicit StackType(bool value);
  };
}
#endif
