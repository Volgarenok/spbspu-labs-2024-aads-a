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
        if (type.value.bracket.symb == ')')
        {
          while (!operandsStack.empty() && operandsStack.top().typeName != nikitov::TypeName::bracket)
          {
            PostfixType newPostfixType;
            newPostfixType.typeName = nikitov::TypeName::operation;
            newPostfixType.value.operation = operandsStack.drop().value.operation;
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
          newStackType.value.bracket = type.value.bracket;
          operandsStack.push(newStackType);
        }
      }
      else
      {
        while (!operandsStack.empty() && operandsStack.top().typeName != nikitov::TypeName::bracket)
        {
          if (type.value.operation <= operandsStack.top().value.operation)
          {
            PostfixType newPostfixType;
            newPostfixType.typeName = nikitov::TypeName::operation;
            newPostfixType.value.operation = operandsStack.drop().value.operation;
            newExpression.push(newPostfixType);
          }
        }
        StackType newStackType;
        newStackType.typeName = nikitov::TypeName::operation;
        newStackType.value.operation = type.value.operation;
        operandsStack.push(newStackType);
      }
    }
    else
    {
      PostfixType newPostfixType;
      newPostfixType.typeName = nikitov::TypeName::operand;
      newPostfixType.value.operand = type.value.operand;
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
    newPostfixType.value.operation = type.value.operation;
    newExpression.push(newPostfixType);
  }
  return newExpression;
}
