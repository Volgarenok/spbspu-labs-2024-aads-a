#ifndef PARTEXPRESSION_HPP
#define PARTEXPRESSION_HPP

namespace piyavkin
{
  namespace detail
  {
    struct Operand
    {
    public:
      Operand();
      Operand(unsigned long long val);
    // private:
      unsigned long long number;
    };
    struct Operation
    {
    public:
      Operation();
      Operation(char val);
      bool operator>(const Operation& rhs);
    // private:
      char operation;
    };
    struct Bracket
    {
    public:
      Bracket();
      Bracket(char val);
    // private:
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
