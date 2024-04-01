#include "convert_expression.hpp"
#include <exception>
#include "queue.hpp"
#include "stack.hpp"
#include "expression_type.hpp"
#include "postfix_expression.hpp"

nikitov::PostfixExpression nikitov::convertExpression(Queue< InfixType > infixExpression)
{
  PostfixExpression postfixExpression;
  Stack< StackType > operandsStack;
  while (!infixExpression.empty())
  {
    InfixType type = infixExpression.drop();
    if (type.typeName == TypeName::operand)
    {
      long long value = type.data.operand.num;
      postfixExpression.add(PostfixType(TypeName::operand, value));
    }
    else
    {
      if (type.typeName == TypeName::bracket)
      {
        if (type.data.bracket.isOpen)
        {
          bool value = type.data.bracket.isOpen;
          operandsStack.push(StackType(TypeName::bracket, value));
        }
        else
        {
          while (!operandsStack.empty() && !operandsStack.top().typeName == nikitov::bracket)
          {
            char value = operandsStack.drop().data.operation.symb;
            postfixExpression.add(PostfixType(TypeName::operation, value));
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
        while (!operandsStack.empty() && operandsStack.top().typeName != TypeName::bracket)
        {
          if (type.data.operation <= operandsStack.top().data.operation)
          {
            char value = operandsStack.drop().data.operation.symb;
            postfixExpression.add(PostfixType(TypeName::operation, value));
          }
          else
          {
            break;
          }
        }
        char value = type.data.operation.symb;
        operandsStack.push(StackType(TypeName::operation, value));
      }
    }
  }

  while (!operandsStack.empty())
  {
    StackType type = operandsStack.drop();
    if (type.typeName == TypeName::bracket)
    {
      throw std::logic_error("Error: Wrong brackets");
    }
    char value = type.data.operation.symb;
    postfixExpression.add(PostfixType(TypeName::operation, value));
  }
  return postfixExpression;
}
