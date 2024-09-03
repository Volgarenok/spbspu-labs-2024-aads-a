#include "calculatePostfix.hpp"
#include <string>
#include <limits>
#include <stdexcept>

long long vyzhanov::performOperation(long long operand1, long long operand2, char operation)
{
  switch (operation)
  {
  case '+':
    return operand1 + operand2;
  case '-':
    return operand1 - operand2;
  case '*':
    return operand1 * operand2;
  case '/':
    if (operand2 == 0)
    {
      throw std::logic_error("Divivsion by zero");
    }
    else
    {
      return operand1 / operand2;
    }
  case '%':
    return operand1 % operand2;
  default:
    return 0;
  }
}

void vyzhanov::calculatePostfix(Queue< Queue< Token > >& expressions, Stack< long long >& results)
{
  while (!expressions.empty())
  {
    Queue< Token > curr = expressions.top();
    Stack< long long > newStack;
    while (!curr.empty())
    {
      Token it = curr.top();
      long long operand1 = 0;
      long long operand2 = 0;
      long long res = 0;
      if (it.getType() == Type::OPERAND)
      {
        newStack.push(it.getOperand());
      }
      else if (it.getType() == Type::OPERATION)
      {
        operand2 = newStack.top();
        newStack.pop();
        operand1 = newStack.top();
        newStack.pop();
        long long maxRes = std::numeric_limits< long long >::max();
        long long minRes = std::numeric_limits< long long >::min();
        if (operand1 > maxRes - operand2 ||(operand2 != 0 && operand1 > maxRes / operand2))
        {
          throw std::out_of_range("Overflow!");
        }
        if (operand1 < minRes + operand2 || (operand1 == minRes && operand2 == -1))
        {
          throw std::out_of_range("Underflow!");
        }
        res = performOperation(operand1, operand2, it.getOperation());
        newStack.push(res);
      }
      curr.pop();
    }
    results.push(newStack.top());
    expressions.pop();
  }
}
