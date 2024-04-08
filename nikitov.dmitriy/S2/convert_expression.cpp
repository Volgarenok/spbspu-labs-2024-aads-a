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
    if (infixValue.type == ExprTypeName::operand)
    {
      long long value = infixValue.operand.num;
      postfixExpression.add(PostfixType(ExprTypeName::operand, value));
    }
    else
    {
      if (infixValue.type == ExprTypeName::bracket)
      {
        if (infixValue.bracket.isOpen)
        {
          bool value = infixValue.bracket.isOpen;
          operandsStack.push(StackType(ExprTypeName::bracket, value));
        }
        else
        {
          while (!operandsStack.empty() && !operandsStack.top().type == nikitov::bracket)
          {
            char value = operandsStack.drop().operation.symb;
            postfixExpression.add(PostfixType(ExprTypeName::operation, value));
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
        while (!operandsStack.empty() && operandsStack.top().type != ExprTypeName::bracket)
        {
          if (infixValue.operation <= operandsStack.top().operation)
          {
            char value = operandsStack.drop().operation.symb;
            postfixExpression.add(PostfixType(ExprTypeName::operation, value));
          }
          else
          {
            break;
          }
        }
        char value = infixValue.operation.symb;
        operandsStack.push(StackType(ExprTypeName::operation, value));
      }
    }
  }

  while (!operandsStack.empty())
  {
    StackType stackValue = operandsStack.drop();
    if (stackValue.type == ExprTypeName::bracket)
    {
      throw std::logic_error("Error: Wrong brackets");
    }
    char value = stackValue.operation.symb;
    postfixExpression.add(PostfixType(ExprTypeName::operation, value));
  }
  return postfixExpression;
}
