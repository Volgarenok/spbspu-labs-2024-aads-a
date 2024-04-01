#ifndef EXPRESSION_TYPE_HPP
#define EXPRESSION_TYPE_HPP

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

    union Data
    {
      Data() = default;
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
    StackType() = default;
    StackType(TypeName type, bool value);
    StackType(TypeName type, char value);

    union Data
    {
      Data() = default;
      Data(bool value);
      Data(char value);

      detail::Bracket bracket;
      detail::Operation operation;
    } data;

    TypeName typeName;
  };

  struct PostfixType
  {
    PostfixType() = default;
    PostfixType(TypeName type, long long value);
    PostfixType(TypeName type, char value);

    union Data
    {
      Data() = default;
      Data(long long value);
      Data(char value);

      detail::Operand operand;
      detail::Operation operation;
    } data;

    TypeName typeName;
  };
}
#endif
