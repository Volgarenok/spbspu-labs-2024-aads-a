#ifndef EXPRESSION_TYPE_HPP
#define EXPRESSION_TYPE_HPP

namespace nikitov
{
  namespace detail
  {
    struct Bracket
    {
      char symb;
    };

    struct Operand
    {
      long long num;
    };

    struct Operation
    {
      bool operator<=(const Operation& other) const;
      char symb;
    };
  }

  enum TypeName
  {
    bracket,
    operand,
    operation
  };

  struct InfixType
  {
    union
    {
      detail::Bracket bracket;
      detail::Operand operand;
      detail::Operation operation;
    };

    TypeName typeName;
  };

  struct StackType
  {
    union
    {
      detail::Bracket bracket;
      detail::Operation operation;
    };

    TypeName typeName;
  };

  struct PostfixType
  {
    union
    {
      detail::Operand operand;
      detail::Operation operation;
    };

    TypeName typeName;
  };
}
#endif
