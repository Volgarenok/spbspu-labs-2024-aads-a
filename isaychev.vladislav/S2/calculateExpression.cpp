#include "calculateExpression.hpp"

void placeOperands(isaychev::Stack< isaychev::Operand > & s, isaychev::Operand n[])
{
  for (int i = 0; i < 2; ++i)
  {
    n[i] = s.top();
    s.pop();
  }
}

long long int isaychev::calculateExpression(Queue< Token > & postfExp)
{
  Stack< Operand > calcStack;
  Operand ops[2] = {};
  while (!postfExp.empty())
  {
    Token t = postfExp.front();
    postfExp.pop();
    if (t.type == TokenType::OPERATION)
    {
      placeOperands(calcStack, ops);
      calcStack.push(t.value.operation(ops[1], ops[0]));
    }
    else if (t.type == TokenType::OPERAND)
    {
      calcStack.push(t.value.operand);
    }
    else
    {
      throw std::invalid_argument("invalid expression");
    }
  }
  return calcStack.top().get_operand();
}
