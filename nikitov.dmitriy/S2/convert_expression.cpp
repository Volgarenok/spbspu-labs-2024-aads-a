#include "convert_expression.hpp"
#include "queue.hpp"
#include "stack.hpp"

nikitov::Queue< nikitov::ExpressionType > nikitov::convertExpression(Queue< ExpressionType >& expression)
{
  Queue< ExpressionType > newExpression;
  Stack< ExpressionType > operandsStack;
  while (!expression.empty())
  {
    ExpressionType type = expression.drop();
    if (type.storedType == 2)
    {
      char symb = type.value.symb;
      if (symb == '(')
      {
        operandsStack.push(type);
      }
      else if (symb == ')')
      {
        while (operandsStack.top().value.symb != '(')
        {
          newExpression.push(operandsStack.drop());
        }
        operandsStack.drop();
      }
      else
      {
        while (!operandsStack.empty() && (type < operandsStack.top()))
        {
          newExpression.push(operandsStack.drop());
        }
        operandsStack.push(type);
      }
    }
    else
    {
      newExpression.push(type);
    }
  }
  while (!operandsStack.empty())
  {
    newExpression.push(operandsStack.drop());
  }
  return newExpression;
}
