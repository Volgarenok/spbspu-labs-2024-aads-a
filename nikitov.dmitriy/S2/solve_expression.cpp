#include "solve_expression.hpp"
#include <exception>
#include <limits>
#include "queue.hpp"
#include "stack.hpp"
#include "expression_type.hpp"

long long nikitov::solveExpression(Queue< ExpressionType > expression)
{
  Stack< ExpressionType > solverStack;
  size_t countElem = 0;
  while (!expression.empty())
  {
    ExpressionType type = expression.drop();
    if (type.storedType == 2)
    {
      if (countElem >= 2)
      {
        long long second = solverStack.drop().value.num;
        long long first = solverStack.drop().value.num;
        long long result = 0;
        char symb = type.value.symb;
        if (symb == '+')
        {
          long long maxNum = std::numeric_limits< long long >::max();
          if (maxNum - first < second)
          {
            throw std::out_of_range("Error: Addition overflow");
          }
          result = first + second;
        }
        else if (symb == '-')
        {
          long long minNum = std::numeric_limits< long long >::min();
          if (minNum + first > second)
          {
            throw std::out_of_range("Error: Subtraction overflow");
          }
          result = first - second;
        }
        else if (symb == '*')
        {
          result = first * second;
          if (second != 0 && result / second != first)
          {
            throw std::out_of_range("Error: Mulptiplication overflow");
          }
        }
        else if (symb == '/')
        {
          long long minNum = std::numeric_limits< long long >::min();
          if (first == minNum && second == -1)
          {
            throw std::out_of_range("Error: Division overflow");
          }
          result = first / second;
        }
        else if (symb == '%')
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
        throw std::logic_error("Error: Wrong order of operations");
      }
    }
    else
    {
      solverStack.push(type);
      ++countElem;
    }
  }
  return solverStack.drop().value.num;
}
