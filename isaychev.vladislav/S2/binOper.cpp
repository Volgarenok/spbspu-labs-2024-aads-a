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

void isaychev::Operation::operator()(const Operand & a, const Operand & b) const
{
  a.get_operand();
  b.get_operand();
}

void isaychev::Operation::set_operation(const std::string & s)
{
  if (s == "+")
  {
    type_ = OperationType::ADD;
  }
  else if (s == "-")
  {
    type_ = OperationType::SUBSTRACT;
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

void isaychev::Operation::add(const Operand & a, const Operand & b) const
{
  a.get_operand();
  b.get_operand();
}

void isaychev::Operation::substruct(const Operand & a, const Operand & b) const
{
  a.get_operand();
  b.get_operand();
}

void isaychev::Operation::multiply(const Operand & a, const Operand & b) const
{
  a.get_operand();
  b.get_operand();
}

void isaychev::Operation::divide(const Operand & a, const Operand & b) const
{
  a.get_operand();
  b.get_operand();
}

void isaychev::Operation::rem_divide(const Operand & a, const Operand & b) const
{
  a.get_operand();
  b.get_operand();
}

int isaychev::Operation::determine_priority(char c)
{
  c += 1;
  return 0;
}
