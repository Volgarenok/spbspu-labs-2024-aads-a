#ifndef EXPRESSION_TYPE_HPP
#define EXPRESSION_TYPE_HPP

namespace nikitov
{
  namespace detail
  {
    struct Bracket
    {
      Bracket(bool value);
      bool isOpen;
    };

    struct Operand
    {
      Operand(long long value);
      long long num;
    };

    struct Operation
    {
      Operation(char value);
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
    InfixType(TypeName type, bool value);
    InfixType(TypeName type, long long value);
    InfixType(TypeName type, char value);

    union Data
    {
      Data(bool value);
      Data(long long value);
      Data(char value);

      detail::Bracket bracket;
      detail::Operand operand;
      detail::Operation operation;
    } data;

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
