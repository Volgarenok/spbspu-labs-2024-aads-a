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
