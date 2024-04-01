#include "solve_expression.hpp"
#include <limits>
#include <exception>
#include "queue.hpp"
#include "stack.hpp"
#include "expression_type.hpp"
#include "postfix_expression.hpp"

long long nikitov::solveExpression(PostfixExpression expression)
{
  Stack< long long > solverStack;
  size_t countElem = 0;
  while (!expression.empty())
  {
    PostfixType type = expression.remove();
    if (type.typeName == TypeName::operation)
    {
      if (countElem >= 2)
      {
        long long second = solverStack.drop();
        long long first = solverStack.drop();
        long long result = 0;
        char symb = type.data.operation.symb;
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
          if (second == 0)
          {
            throw std::logic_error("Error: Division by zero");
          }
          if (first == minNum && second == -1)
          {
            throw std::out_of_range("Error: Division overflow");
          }
          result = first / second;
        }
        else if (symb == '%')
        {
          result = first % second;
          if (result < 0)
          {
            result += second;
          }
        }
        solverStack.push(result);
        --countElem;
      }
      else
      {
        throw std::logic_error("Error: Wrong order of operations");
      }
    }
    else
    {
      solverStack.push(type.data.operand.num);
      ++countElem;
    }
  }
  return solverStack.drop();
}
