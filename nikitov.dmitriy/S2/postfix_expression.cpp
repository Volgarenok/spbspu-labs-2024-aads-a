#include "postfix_expression.hpp"

void inputOperator(nikitov::PostfixExpression& expression, char symb, long long value)
{
  nikitov::PostfixType operation;
  operation.typeName = nikitov::TypeName::operation;
  operation.operation.symb = symb;
  expression.add(operation);

  nikitov::PostfixType operand;
  operand.typeName = nikitov::TypeName::operand;
  operand.operand.num = value;
  expression.add(operand);
}

nikitov::PostfixExpression nikitov::PostfixExpression::operator+(long long value) const
{
  PostfixExpression newExpression(*this);
  inputOperator(newExpression, '+', value);
  return newExpression;
}

nikitov::PostfixExpression nikitov::PostfixExpression::operator-(long long value) const
{
  PostfixExpression newExpression(*this);
  inputOperator(newExpression, '-', value);
  return newExpression;
}

nikitov::PostfixExpression nikitov::PostfixExpression::operator*(long long value) const
{
  PostfixExpression newExpression(*this);
  inputOperator(newExpression, '*', value);
  return newExpression;
}

nikitov::PostfixExpression nikitov::PostfixExpression::operator/(long long value) const
{
  PostfixExpression newExpression(*this);
  inputOperator(newExpression, '/', value);
  return newExpression;
}

nikitov::PostfixExpression nikitov::PostfixExpression::operator%(long long value) const
{
  PostfixExpression newExpression(*this);
  inputOperator(newExpression, '%', value);
  return newExpression;
}

void nikitov::PostfixExpression::add(PostfixType& value)
{
  data.push(value);
}

nikitov::PostfixType nikitov::PostfixExpression::remove()
{
  return data.drop();
}

size_t nikitov::PostfixExpression::size() const
{
  return data.size();
}

bool nikitov::PostfixExpression::empty() const
{
  return data.empty();
}
