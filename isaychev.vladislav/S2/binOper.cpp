#include "binOper.hpp"

isaychev::Operation::Operation():
 type_(OperationType::UNKNOWN),
 priority_(0)
{}

isaychev::Operation::Operation(std::string s)
{
  set_operation(s);
  //type_ = determine_priority();
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
  a.get_operand();
  b.get_operand();
  return Operand(0);
}

isaychev::Operand isaychev::Operation::subtract(const Operand & a, const Operand & b) const
{
  a.get_operand();
  b.get_operand();
  return Operand(0);
}

isaychev::Operand isaychev::Operation::multiply(const Operand & a, const Operand & b) const
{
  a.get_operand();
  b.get_operand();
  return Operand(0);
}

isaychev::Operand isaychev::Operation::divide(const Operand & a, const Operand & b) const
{
  a.get_operand();
  b.get_operand();
  return Operand(0);
}

isaychev::Operand isaychev::Operation::rem_divide(const Operand & a, const Operand & b) const
{
  a.get_operand();
  b.get_operand();
  return Operand(0);
}

int isaychev::Operation::determine_priority(char c)
{
  c += 1;
  return 0;
}
