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

    bool& getBracket();
    char& getOperation();
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
