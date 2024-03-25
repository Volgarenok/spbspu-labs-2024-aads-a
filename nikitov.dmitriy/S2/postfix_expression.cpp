#include "postfix_expression.hpp"

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