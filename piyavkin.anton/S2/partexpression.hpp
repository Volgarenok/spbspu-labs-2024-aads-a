#ifndef PARTEXPRESSION_HPP
#define PARTEXPRESSION_HPP

namespace piyavkin
{
  namespace detail
  {
    struct Operand
    {
      Operand();
      Operand(unsigned long long val);
      unsigned long long number;
    };
    struct Operation
    {
      Operation();
      Operation(char val);
      char operation;
      bool operator>(const Operation& rhs);
    };
    struct Bracket
    {
      Bracket();
      Bracket(char val);
      char bracket;
    };
    enum TypesPartsExpression
    {
      operand = 0,
      operation = 1,
      bracket = 2
    };
  }
}
#endif
