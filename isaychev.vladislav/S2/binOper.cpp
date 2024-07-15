#include "binOper.hpp"
#include <limits>
#include <stdexcept>

isaychev::Operation::Operation():
 type_(OperationType::UNKNOWN)
{}

isaychev::Operation::Operation(std::string s)
{
  set_operation(s);
}

isaychev::Operand isaychev::Operation::operator()(const Operand & a, const Operand & b) const
{
  if (type_ == OperationType::ADD)
  {
    return add(a, b);
  }
  else if (type_ == OperationType::SUBTRACT)
  {
    return subtract(a, b);
  }
  else if (type_ == OperationType::MULTIPLY)
  {
    return multiply(a, b);
  }
  else if (type_ == OperationType::DIVIDE)
  {
    return divide(a, b);
  }
  else if (type_ == OperationType::REM_DIVIDE)
  {
    return rem_divide(a, b);
  }
  return Operand(0);
}

void isaychev::Operation::set_operation(const std::string & s)
{
  if (s == "+")
  {
    type_ = OperationType::ADD;
  }
  else if (s == "-")
  {
    type_ = OperationType::SUBTRACT;
  }
  else if (s == "*")
  {
    type_ = OperationType::MULTIPLY;
  }
  else if (s == "/")
  {
    type_ = OperationType::DIVIDE;
  }
  else if (s == "%")
  {
    type_ = OperationType::REM_DIVIDE;
  }
  else
  {
    type_ = OperationType::UNKNOWN;
  }
}

isaychev::Operand isaychev::Operation::add(const Operand & a, const Operand & b) const
{
  long long int max = std::numeric_limits< long long int >::max();
  if (max - a.get_operand() < b.get_operand())
  {
    throw std::overflow_error("addition overflow");
  }
  return Operand(a.get_operand() + b.get_operand());
}

isaychev::Operand isaychev::Operation::subtract(const Operand & a, const Operand & b) const
{
  return Operand(a.get_operand() - b.get_operand());
}

isaychev::Operand isaychev::Operation::multiply(const Operand & a, const Operand & b) const
{
  long long int max = std::numeric_limits< long long int >::max();
  long long int n1 = a.get_operand(), n2 = b.get_operand();
  if (n2 != 0 && (max / std::abs(n2) < std::abs(n1)))
  {
    throw std::overflow_error("multiplication overflow");
  }
  return Operand(n1 * n2);
}

isaychev::Operand isaychev::Operation::divide(const Operand & a, const Operand & b) const
{
  if (b.get_operand() == 0)
  {
    throw std::logic_error("division by zero");
  }
  return Operand(a.get_operand() / b.get_operand());
}

isaychev::Operand isaychev::Operation::rem_divide(const Operand & a, const Operand & b) const
{
  if (a.get_operand() == 0)
  {
    throw std::logic_error("mod zero");
  }
  return Operand(a.get_operand() % b.get_operand());
}

int isaychev::Operation::get_priority() const
{
  if (type_ == OperationType::ADD)
  {
    return 2;
  }
  else if (type_ == OperationType::SUBTRACT)
  {
    return 2;
  }
  else if (type_ == OperationType::MULTIPLY)
  {
    return 1;
  }
  else if (type_ == OperationType::DIVIDE)
  {
    return 1;
  }
  else if (type_ == OperationType::REM_DIVIDE)
  {
    return 1;
  }
  return 0;
}
