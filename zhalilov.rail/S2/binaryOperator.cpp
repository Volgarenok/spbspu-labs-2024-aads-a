#include "binaryOperator.hpp"

#include "operand.hpp"

zhalilov::BinOperator::BinOperator(Type type):
  type_(type)
{}

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
