#include "binOper.hpp"
#include <limits>
#include <stdexcept>

isaychev::Operation::Operation():
 type_(OperationType::UNKNOWN),
 priority_(0)
{}

isaychev::Operation::Operation(char c):
 type_(OperationType::UNKNOWN),
 priority_(0)
{
  if (c == '+')
  {
    type_ = OperationType::ADD;
    priority_ = 2;
  }
  else if (c == '-')
  {
    type_ = OperationType::SUBTRACT;
    priority_ = 2;
  }
  else if (c == '*')
  {
    type_ = OperationType::MULTIPLY;
    priority_ = 1;
  }
  else if (c == '/')
  {
    type_ = OperationType::DIVIDE;
    priority_ = 1;
  }
  else if (c == '%')
  {
    type_ = OperationType::MOD;
    priority_ = 1;
  }
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
  else if (type_ == OperationType::MOD)
  {
    return mod(a, b);
  }
  return Operand(0);
}

isaychev::OperationType isaychev::Operation::get_type() const noexcept
{
  return type_;
}

bool isaychev::Operation::operator<(const Operation & rhs) const noexcept
{
  return priority_ < rhs.priority_;
}

bool isaychev::Operation::operator>(const Operation & rhs) const noexcept
{
  return priority_ > rhs.priority_;
}

bool isaychev::Operation::operator<=(const Operation & rhs) const noexcept
{
  return priority_ <= rhs.priority_;
}

bool isaychev::Operation::operator>=(const Operation & rhs) const noexcept
{
  return priority_ >= rhs.priority_;
}

bool isaychev::Operation::operator==(const Operation & rhs) const noexcept
{
  return priority_ == rhs.priority_;
}

bool isaychev::Operation::operator!=(const Operation & rhs) const noexcept
{
  return priority_ != rhs.priority_;
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

isaychev::Operand isaychev::Operation::mod(const Operand & a, const Operand & b) const
{
  if (a.get_operand() == 0)
  {
    throw std::logic_error("mod zero");
  }
  long long int n = a.get_operand() % b.get_operand();
  if (n < 0)
  {
    n += b.get_operand();
  }
  return Operand(n);
}
