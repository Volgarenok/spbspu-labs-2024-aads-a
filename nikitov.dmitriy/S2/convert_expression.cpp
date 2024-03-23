#include "convert_expression.hpp"
#include <exception>
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
      if (symb == ')')
      {
        while (operandsStack.top().value.symb != '(')
        {
          if (operandsStack.empty())
          {
            throw std::logic_error("Error: Wrong brackets");
          }
          newExpression.push(operandsStack.drop());
        }
        operandsStack.drop();
      }
      else
      {
        if (symb != '(')
        {
          while (!operandsStack.empty() && (type <= operandsStack.top()))
          {
            newExpression.push(operandsStack.drop());
          }
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
    ExpressionType type = operandsStack.drop();
    if (type.value.symb == '(')
    {
      throw std::logic_error("Error: Wrong brackets");
    }
    newExpression.push(type);
  }
  return newExpression;
}
