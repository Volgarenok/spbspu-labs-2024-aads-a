#include "calculateExpression.hpp"

long long int isaychev::calculateExpression(Queue< Token > & postfExp)
{
  Stack< Operand > calcStack;
  while (!postfExp.empty())
  {
    Token t = postfExp.front();
    postfExp.pop();
    if (t.type == TokenType::OPERATION)
    {
      Operand b = calcStack.top();
      calcStack.pop();
      Operand a = calcStack.top();
      calcStack.pop();
      calcStack.push(t.value.operation(a, b));
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
