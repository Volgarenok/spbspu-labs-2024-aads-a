#include "convert_expression.hpp"
#include <exception>
#include "queue.hpp"
#include <iostream>
#include "stack.hpp"

nikitov::Queue< nikitov::PostfixType > nikitov::convertExpression(Queue< InfixType >& expression)
{
  Queue< PostfixType > newExpression;
  Stack< StackType > operandsStack;
  while (!expression.empty())
  {
    InfixType type = expression.drop();
    if (type.typeName != nikitov::TypeName::operand)
    {
      if (type.typeName == nikitov::TypeName::bracket)
      {
        if (type.bracket.symb == ')')
        {
          while (!operandsStack.empty() && operandsStack.top().typeName != nikitov::TypeName::bracket)
          {
            PostfixType newPostfixType;
            newPostfixType.typeName = nikitov::TypeName::operation;
            newPostfixType.operation = operandsStack.drop().operation;
            newExpression.push(newPostfixType);
          }
          if (operandsStack.empty())
          {
            throw std::logic_error("Error: Wrong brackets");
          }
          operandsStack.drop();
        }
        else
        {
          StackType newStackType;
          newStackType.typeName = nikitov::TypeName::bracket;
          newStackType.bracket = type.bracket;
          operandsStack.push(newStackType);
        }
      }
      else
      {
        while (!operandsStack.empty() && operandsStack.top().typeName != nikitov::TypeName::bracket)
        {
          if (type.operation <= operandsStack.top().operation)
          {
            PostfixType newPostfixType;
            newPostfixType.typeName = nikitov::TypeName::operation;
            newPostfixType.operation = operandsStack.drop().operation;
            newExpression.push(newPostfixType);
          }
          else
          {
            break;
          }
        }
        StackType newStackType;
        newStackType.typeName = nikitov::TypeName::operation;
        newStackType.operation = type.operation;
        operandsStack.push(newStackType);
      }
    }
    else
    {
      PostfixType newPostfixType;
      newPostfixType.typeName = nikitov::TypeName::operand;
      newPostfixType.operand = type.operand;
      newExpression.push(newPostfixType);
    }
  }

  while (!operandsStack.empty())
  {
    StackType type = operandsStack.drop();
    if (type.typeName == nikitov::TypeName::bracket)
    {
      throw std::logic_error("Error: Wrong brackets");
    }
    PostfixType newPostfixType;
    newPostfixType.typeName = nikitov::TypeName::operation;
    newPostfixType.operation = type.operation;
    newExpression.push(newPostfixType);
  }
  return newExpression;
}
