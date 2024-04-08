#ifndef EXPRESSION_TYPES_HPP
#define EXPRESSION_TYPES_HPP

namespace nikitov
{
  namespace detail
  {
    struct Bracket
    {
      Bracket() = default;
      Bracket(bool value);
      bool isOpen;
    };

    struct Operand
    {
      Operand() = default;
      Operand(long long value);
      long long num;
    };

    struct Operation
    {
      Operation() = default;
      Operation(char value);
      bool operator<=(const Operation& other) const;
      char symb;
    };
  }

  enum ExprTypeName
  {
    bracket,
    operand,
    operation
  };

  struct InfixType
  {
    InfixType() = default;
    InfixType(ExprTypeName type, bool value);
    InfixType(ExprTypeName type, long long value);
    InfixType(ExprTypeName type, char value);

    union
    {
      detail::Bracket bracket;
      detail::Operand operand;
      detail::Operation operation;
    };
    ExprTypeName type;
  };

  struct StackType
  {
    StackType() = default;
    explicit StackType(ExprTypeName type, bool value);
    explicit StackType(ExprTypeName type, char value);

    union
    {
      detail::Bracket bracket;
      detail::Operation operation;
    };
    ExprTypeName type;
  };

  struct PostfixType
  {
    PostfixType() = default;
    explicit PostfixType(ExprTypeName type, long long value);
    explicit PostfixType(ExprTypeName type, char value);

    union
    {
      detail::Operand operand;
      detail::Operation operation;
    };
    ExprTypeName type;
  };
}
#endif
