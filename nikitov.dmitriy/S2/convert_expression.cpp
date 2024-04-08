#include "convert_expression.hpp"
#include <exception>
#include "queue.hpp"
#include "stack.hpp"
#include "expression_types.hpp"
#include "postfix_expression.hpp"

nikitov::PostfixExpression nikitov::convertExpression(Queue< InfixType > infixExpression)
{
  PostfixExpression postfixExpression;
  Stack< StackType > operandsStack;
  while (!infixExpression.empty())
  {
    InfixType infixValue = infixExpression.drop();
    if (infixValue.getType() == ExprTypeName::operand)
    {
      long long value = infixValue.getOperand();
      postfixExpression.add(PostfixType(value));
    }
    else
    {
      if (infixValue.getType() == ExprTypeName::bracket)
      {
        if (infixValue.getBracket())
        {
          bool value = infixValue.getBracket();
          operandsStack.push(StackType(value));
        }
        else
        {
          while (!operandsStack.empty() && !operandsStack.top().getType() == nikitov::bracket)
          {
            char value = operandsStack.drop().getOperation();
            postfixExpression.add(PostfixType(value));
          }
          if (operandsStack.empty())
          {
            throw std::logic_error("Error: Wrong brackets");
          }
          operandsStack.drop();
        }
      }
      else
      {
        while (!operandsStack.empty() && operandsStack.top().getType() != ExprTypeName::bracket)
        {
          if (infixValue.operation <= operandsStack.top().operation)
          {
            char value = operandsStack.drop().getOperation();
            postfixExpression.add(PostfixType(value));
          }
          else
          {
            break;
          }
        }
        char value = infixValue.getOperation();
        operandsStack.push(StackType(value));
      }
    }
  }

  while (!operandsStack.empty())
  {
    StackType stackValue = operandsStack.drop();
    if (stackValue.getType() == ExprTypeName::bracket)
    {
      throw std::logic_error("Error: Wrong brackets");
    }
    char value = stackValue.getOperation();
    postfixExpression.add(PostfixType(value));
  }
  return postfixExpression;
}
