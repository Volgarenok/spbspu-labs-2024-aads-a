#include "operation.hpp"
#include <stdexcept>

baranov::Operation::Operation(char c)
{
  switch (c)
  {
    case '+':
      type_ = OperationType::ADDITION;
      break;
    case '-':
       type_ = OperationType::SUBTRACTION;
       break;
    case '*':
       type_ = OperationType::MULTIPLICATION;
       break;
    case '/':
       type_ = OperationType::DIVISION;
       break;
    case '%':
       type_ = OperationType::MODULATION;
       break;
    default:
       throw std::logic_error("Invalid operation sign");
  }
}

unsigned char baranov::Operation::getPriority() const
{
  unsigned char priority = 0;
  if (type_ == OperationType::ADDITION || type_ == OperationType::SUBTRACTION)
  {
    priority = 2;
  }
  else
  {
    priority = 1;
  }
  return priority;
}

bool baranov::Operation::operator<=(const Operation & rhs)
{
  return getPriority() <= rhs.getPriority();
}

baranov::OperationType baranov::Operation::getType() const
{
  return type_;
}

