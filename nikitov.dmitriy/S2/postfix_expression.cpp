#include "postfix_expression.hpp"

void inputOperator(nikitov::PostfixExpression& expression, char symb, long long value)
{
  expression.add(nikitov::PostfixType(nikitov::TypeName::operation, symb));
  expression.add(nikitov::PostfixType(nikitov::TypeName::operand, value));
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

void nikitov::PostfixExpression::add(PostfixType&& value)
{
  data.push(std::move(value));
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
