#ifndef EXPRESSION_TYPES_HPP
#define EXPRESSION_TYPES_HPP

namespace namestnikov
{
  struct Operand
  {
    long long number;
    explicit Operand(long long data);
  };
  struct Operation
  {
    char operation;
    explicit Operation(char operation);
    bool operator>(const Operation & other);
  };
  struct Bracket
  {
    char bracket;
    bool isOpen;
    Bracket(char bracket, bool isOpen);
  };
  enum ExpressionTypes {operand, operation, bracket};
}

#endif
