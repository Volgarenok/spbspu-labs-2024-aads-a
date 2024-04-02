#include "operator.hpp"
#include "stdexcept"

erohin::Operator::Operator(char sign)
{
  switch (sign)
  {
    case '-':
      type_ = operator_t::OPERATOR_SUBTRACT;
      break;

    default:
      throw std::logic_error("Unknown operation");
  }
}

unsigned short erohin::Operator::priority()
{
  return 0;
}

erohin::Operand erohin::Operator::evaluate(const Operand & lhs, const Operand & rhs)
{
  Operand op(rhs);
  return Operand(lhs);
}
