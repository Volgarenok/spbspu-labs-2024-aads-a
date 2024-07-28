#include "calculatePostfix.hpp"
#include <string>
#include <limits>
#include <stdexcept>

long long vyzhanov::performOperation(long long operand1, long long operand2, char operation)
{
  switch (operation) {
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
    return operand1 / operand2;
  case '%':
    return operand1 % operand2;
  default:
    return 0;
  }
}

void vyzhanov::calculatePostfix(Queue< Queue< char > >& expressions,
  Stack< long long >& results)
{
  while (!expressions.empty())
  {
    Queue< char > curr = expressions.top();
    Stack< long long > newStack;
    while (!curr.empty())
    {
      char it = curr.top();
      if (std::isdigit(it))
      {
        newStack.push(it - '0');
        curr.pop();
      }
      else
      {
        long long operand2 = newStack.top();
        newStack.pop();
        long long operand1 = newStack.top();
        newStack.pop();
        long long mult = operand1 * operand2;
        long long maxRes = std::numeric_limits< long long >::max();
        long long minRes = std::numeric_limits< long long >::min();
        if (operand1 > maxRes - operand2 ||(operand2 != 0 && operand1 == mult / operand2))
        {
          throw std::out_of_range("Overflow!");
        }
        if (operand1 < minRes + operand2 || (operand1 == minRes && operand2 == -1))
        {
          throw std::out_of_range("Underflow!");
        }
        long long result = performOperation(operand1, operand2, it);
        newStack.push(result);
        curr.pop();
      }
    }
    results.push(newStack.top());
    expressions.pop();
  }
}
