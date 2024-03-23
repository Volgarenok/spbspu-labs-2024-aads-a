#include "solve_expression.hpp"
#include "queue.hpp"
#include "stack.hpp"
#include "expression_type.hpp"

long long int nikitov::solveExpression(Queue< ExpressionType > expression)
{
  Stack< ExpressionType > solverStack;
  size_t countElem = 0;
  while (!expression.empty())
  {
    ExpressionType type = expression.drop();
    if (type.storedType == 1)
    {
      solverStack.push(type);
      ++countElem;
    }
    else
    {
      if (countElem >= 2)
      {
        long long int second = solverStack.drop().value.num;
        long long int first = solverStack.drop().value.num;
        long long int result = 0;
        char symb = type.value.symb;
        if (symb == '+')
        {
          result = first + second;
        }
        else if (symb == '-')
        {
          result = first - second;
        }
        else if (symb == '*')
        {
          result = first * second;
        }
        else if (symb == '/')
        {
          result = first / second;
        }
        else
        {
          result = first % second;
        }
        ExpressionType newType;
        newType.value.num = result;
        newType.storedType = 1;
        solverStack.push(newType);
        --countElem;
      }
      else
      {
      }
    }
  }
  return solverStack.drop().value.num;
}