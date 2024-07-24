#include "operator.hpp"
#include <stdexcept>

erohin::Operator::Operator(char sign)
{
  switch (sign)
  {
  case '-':
    type_ = operator_t::OPERATOR_SUBTRACT;
    break;
  case '+':
    type_ = operator_t::OPERATOR_ADD;
    break;
  case '*':
    type_ = operator_t::OPERATOR_MULTIPLY;
    break;
  case '/':
    type_ = operator_t::OPERATOR_DIVIDE;
    break;
  case '%':
    type_ = operator_t::OPERATOR_MOD;
    break;
  default:
    throw std::logic_error("Unknown operation");
  }
}

unsigned short erohin::Operator::priority() const
{
  unsigned short priority_number = 0;
  switch (type_)
  {
  case operator_t::OPERATOR_SUBTRACT:
    priority_number = 2;
    break;
  case operator_t::OPERATOR_ADD:
    priority_number = 2;
    break;
  case operator_t::OPERATOR_MULTIPLY:
    priority_number = 1;
    break;
  case operator_t::OPERATOR_DIVIDE:
    priority_number = 1;
    break;
  case operator_t::OPERATOR_MOD:
    priority_number = 1;
    break;
  }
  return priority_number;
}

erohin::Operand erohin::Operator::evaluate(const Operand & lhs, const Operand & rhs) const
{
  Operand result;
  switch (type_)
  {
  case operator_t::OPERATOR_SUBTRACT:
    result = subtract(lhs, rhs);
    break;
  case operator_t::OPERATOR_ADD:
    result = add(lhs, rhs);
    break;
  case operator_t::OPERATOR_MULTIPLY:
    result = multiply(lhs, rhs);
    break;
  case operator_t::OPERATOR_DIVIDE:
    result = divide(lhs, rhs);
    break;
  case operator_t::OPERATOR_MOD:
    result = mod(lhs, rhs);
    break;
  }
  return result;
}

bool erohin::operator>=(const Operator & lhs, const Operator & rhs)
{
  return lhs.priority() >= rhs.priority();
}

erohin::Operand erohin::subtract(const Operand & lhs, const Operand & rhs)
{
  if (rhs() > 0 && lhs() < limit_t::MIN + rhs())
  {
    throw std::underflow_error("Substraction caused underflow");
  }
  else if (rhs() < 0 && lhs() > limit_t::MAX + rhs())
  {
    throw std::overflow_error("Substraction caused overflow");
  }
  return Operand(lhs() - rhs());
}

erohin::Operand erohin::add(const Operand & lhs, const Operand & rhs)
{
  if (rhs() < 0 && lhs() < limit_t::MIN - rhs())
  {
    throw std::underflow_error("Addition caused underflow");
  }
  else if (rhs() > 0 && lhs() > limit_t::MAX - rhs())
  {
    throw std::overflow_error("Addition caused overflow");
  }
  return Operand(lhs() + rhs());
}

erohin::Operand erohin::multiply(const Operand & lhs, const Operand & rhs)
{
  if (rhs() > 0 && lhs() > 0 && lhs() > limit_t::MAX / rhs())
  {
    throw std::overflow_error("Multiplication caused overflow");
  }
  else if (rhs() < 0 && lhs() < 0 && lhs() < limit_t::MAX / rhs())
  {
    throw std::overflow_error("Multiplication caused overflow");
  }
  else if (rhs() > 0 && lhs() < 0 && lhs() < limit_t::MIN / rhs())
  {
    throw std::underflow_error("Multiplication caused underflow");
  }
  else if (rhs() < 0 && lhs() > 0 && lhs() > limit_t::MIN / rhs())
  {
    throw std::underflow_error("Multiplication caused underflow");
  }
  return Operand(lhs() * rhs());
}

erohin::Operand erohin::divide(const Operand & lhs, const Operand & rhs)
{
  if (rhs() == 0)
  {
    throw std::invalid_argument("Division by 0");
  }
  else if (lhs() == limit_t::MIN && rhs() == -1)
  {
    throw std::overflow_error("Division caused overflow");
  }
  return Operand(lhs() / rhs());
}

erohin::Operand erohin::mod(const Operand & lhs, const Operand & rhs)
{
  if (rhs() == 0)
  {
    throw std::invalid_argument("Division by 0");
  }
  long long res = lhs() % rhs();
  bool isSameSign = (rhs() > 0 && lhs() > 0) || (rhs() < 0 && lhs() < 0);
  return (isSameSign) ? res : (rhs() + res);
}
