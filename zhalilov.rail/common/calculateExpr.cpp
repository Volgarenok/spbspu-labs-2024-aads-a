#include "calculateExpr.hpp"

#include "expressionTokens.hpp"
#include "primaryType.hpp"
#include "operand.hpp"
#include "binaryOperator.hpp"
#include "stack.hpp"

long long zhalilov::calculateExpr(Queue< PostfixToken > expr)
{
  Stack< Operand > operands;
  while (!expr.empty())
  {
    PostfixToken tempToken = expr.front();
    if (tempToken.getType() == PrimaryType::BinOperator)
    {
      if (operands.size() < 2)
      {
        throw std::invalid_argument("incorrect expression");
      }
      Operand last = operands.top();
      operands.pop();
      Operand nextToLast = operands.top();
      operands.pop();
      operands.push(tempToken.getBinOperator()(nextToLast, last));
    }
    else
    {
      operands.push(tempToken.getOperand());
    }
    expr.pop();
  }
  if (operands.size() != 1)
  {
    throw std::invalid_argument("incorrect expression");
  }
  return operands.top().getNum();
}
