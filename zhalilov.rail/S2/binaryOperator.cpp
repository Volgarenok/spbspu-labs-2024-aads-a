#include "binaryOperator.hpp"

#include <stdexcept>

#include "operand.hpp"

zhalilov::BinOperator::BinOperator():
  type_(BinOperator::Type::Undefined)
{}

zhalilov::BinOperator::BinOperator(Type type):
  type_(type)
{}

zhalilov::BinOperator::BinOperator(char symb)
{
  switch (symb)
  {
  case '+':
    type_ = BinOperator::Type::Add;
    break;
  case '-':
    type_ = BinOperator::Type::Subtraction;
    break;
  case '*':
    type_ = BinOperator::Type::Multiply;
    break;
  case '/':
    type_ = BinOperator::Type::Division;
    break;
  case '%':
    type_ = BinOperator::Type::Mod;
    break;
  }
  if (type_ == BinOperator::Type::Undefined)
  {
    throw std::invalid_argument("symbol isn't binary operator");
  }
}

zhalilov::Operand zhalilov::BinOperator::operator()(const Operand &left, const Operand &right) const
{
  switch (type_)
  {
  case Type::Add:
    return Operand(left.getNum() + right.getNum());
  case Type::Subtraction:
    return Operand(left.getNum() - right.getNum());
  case Type::Multiply:
    return Operand(left.getNum() * right.getNum());
  case Type::Division:
    return Operand(left.getNum() / right.getNum());
  case Type::Mod:
    return Operand(left.getNum() % right.getNum());
  default:
    return Operand(0);
  }
}

unsigned short zhalilov::BinOperator::getPriority() const
{
  switch (type_)
  {
  case Type::Add:
    return 2;
  case Type::Subtraction:
    return 2;
  case Type::Multiply:
    return 1;
  case Type::Division:
    return 1;
  case Type::Mod:
    return 1;
  default:
    return 0;
  }
}

bool zhalilov::BinOperator::operator<(const BinOperator &other) const
{
  return getPriority() < other.getPriority();
}

bool zhalilov::BinOperator::operator>(const BinOperator &other) const
{
  return getPriority() > other.getPriority();
}

bool zhalilov::BinOperator::operator==(const BinOperator &other) const
{
  return getPriority() == other.getPriority();
}

bool zhalilov::BinOperator::operator!=(const BinOperator &other) const
{
  return getPriority() != other.getPriority();
}

bool zhalilov::BinOperator::operator<=(const BinOperator &other) const
{
  return getPriority() <= other.getPriority();
}

bool zhalilov::BinOperator::operator>=(const BinOperator &other) const
{
  return getPriority() >= other.getPriority();
}
