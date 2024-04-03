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

  union Data
  {
    Data() = default;
    Data(bool value);
    Data(long long value);
    Data(char value);

    detail::Bracket bracket;
    detail::Operand operand;
    detail::Operation operation;
  };

  enum TypeName
  {
    bracket,
    operand,
    operation
  };

  struct InfixType
  {
    InfixType() = default;
    InfixType(TypeName type, bool value);
    InfixType(TypeName type, long long value);
    InfixType(TypeName type, char value);

    Data data;
    TypeName typeName;
  };

  struct StackType
  {
    StackType() = default;
    explicit StackType(TypeName type, bool value);
    explicit StackType(TypeName type, char value);

    Data data;
    TypeName typeName;
  };

  struct PostfixType
  {
    PostfixType() = default;
    explicit PostfixType(TypeName type, long long value);
    explicit PostfixType(TypeName type, char value);

    Data data;
    TypeName typeName;
  };
}
#endif
