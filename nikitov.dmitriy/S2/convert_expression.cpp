#include "convert_expression.hpp"
#include <exception>
#include <queue.hpp>
#include <stack.hpp>
#include "infix_type.hpp"
#include "stack_type.hpp"
#include "postfix_type.hpp"
#include "postfix_expression.hpp"

bool isLessPriority(char left, char right)
{
  if (left == '+' || left == '-')
  {
    return true;
  }
  else
  {
    return right == '*' || right == '/' || right == '%';
  }
}

nikitov::PostfixExpression nikitov::convertExpression(Queue< InfixType > infixExpression)
{
  Queue< PostfixType > postfixQueue;
  Stack< StackType > operandsStack;
  while (!infixExpression.empty())
  {
    InfixType infixValue = infixExpression.top();
    infixExpression.pop();
    if (infixValue.getType() == ExprTypeName::operand)
    {
      long long value = infixValue.getOperand();
      postfixQueue.push(PostfixType(value));
    }
    else
    {
      if (infixValue.getType() == ExprTypeName::bracket)
      {
        if (infixValue.isOpenBracket())
        {
          bool isOpenBracket = infixValue.isOpenBracket();
          if (isOpenBracket)
          {
            operandsStack.push(StackType::openBracket());
          }
          else
          {
            operandsStack.push(StackType::closeBracket());
          }
        }
        else
        {
          while (!operandsStack.empty() && !(operandsStack.top().getType() == ExprTypeName::bracket))
          {
            char value = operandsStack.top().getOperation();
            operandsStack.pop();
            postfixQueue.push(PostfixType(value));
          }
          if (operandsStack.empty())
          {
            throw std::logic_error("Error: Wrong brackets");
          }
          operandsStack.pop();
        }
      }
      else
      {
        while (!operandsStack.empty() && operandsStack.top().getType() != ExprTypeName::bracket)
        {
          if (isLessPriority(infixValue.getOperation(), operandsStack.top().getOperation()))
          {
            char value = operandsStack.top().getOperation();
            operandsStack.pop();
            postfixQueue.push(PostfixType(value));
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
    StackType stackValue = operandsStack.top();
    operandsStack.pop();
    if (stackValue.getType() == ExprTypeName::bracket)
    {
      throw std::logic_error("Error: Wrong brackets");
    }
    char value = stackValue.getOperation();
    postfixQueue.push(PostfixType(value));
  }

  return PostfixExpression(postfixQueue);
}
