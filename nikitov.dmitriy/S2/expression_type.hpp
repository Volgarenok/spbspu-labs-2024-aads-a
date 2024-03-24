#ifndef EXPRESSION_TYPE_HPP
#define EXPRESSION_TYPE_HPP

#include <cstddef>


namespace nikitov
{
  enum TypeName
  {
    bracket,
    operand,
    operation
  };

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

  struct InfixType
  {
    union
    {
      Bracket bracket;
      Operand operand;
      Operation operation;
    } value;

    TypeName typeName;
  };

  struct StackType
  {
    union
    {
      Bracket bracket;
      Operation operation;
    } value;

    TypeName typeName;
  };

  struct PostfixType
  {
    union
    {
      Operand operand;
      Operation operation;
    } value;

    TypeName typeName;
  };
}
#endif
