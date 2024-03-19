#ifndef PARTEXPRESSION_HPP
#define PARTEXPRESSION_HPP

namespace piyavkin
{
  class PartExpression
  {};

  class Operand: public PartExpression
  {
    int operand;
  };

  class Operation: public PartExpression
  {
    char operation;
  };
}
#endif