#include "calculate_postfix.hpp"
#include <stdexcept>
#include <limits>
#include "stack.hpp"

bool isAdditionOverflow(long long num1, long long num2)
{
  const long long max = std::numeric_limits< long long >::max();
  const long long min = std::numeric_limits< long long >::min();
  if (num1 > 0 && num2 > 0 && (max - num1 < num2))
  {
    return true;
  }
  if (num1 < 0 && num2 < 0 && (min - num1 > num2))
  {
    return true;
  }
  return false;
}

bool isSubtractionOverflow(long long num1, long long num2)
{
  return isAdditionOverflow(num1, - num2);
}

bool isMultiplicationOverflow(long long num1, long long num2)
{
  if (num1 == 0 || num2 == 0)
  {
    return false;
  }
  const long long max = std::numeric_limits< long long >::max();
  if (std::abs(num1) > max / std::abs(num2))
  {
    return true;
  }
  return false;
}

long long lopatina::calculatePostfix(Queue< PostfixType > & queue_postfix)
{
  Stack< long long > stack_process;

  while (!queue_postfix.empty())
  {
    PostfixType elem = queue_postfix.front();
    if (elem.getType() == OPERAND)
    {
      stack_process.push(elem.getOperand());
    }
    else if (elem.getType() == OPERATION)
    {
      if (stack_process.empty())
      {
        throw std::logic_error("Wrong math expression");
      }
      long long num2 = stack_process.top();
      stack_process.pop();
      if (stack_process.empty())
      {
        throw std::logic_error("Wrong math expression");
      }
      long long num1 = stack_process.top();
      stack_process.pop();
      char operation = elem.getOperation();
      if (operation == '+')
      {
        if (isAdditionOverflow(num1, num2))
        {
          throw std::logic_error("Overflow during addition");
        }
        stack_process.push(num1 + num2);
      }
      else if (operation == '-')
      {
        if (isSubtractionOverflow(num1, num2))
        {
          throw std::logic_error("Overflow during substraction");
        }
        stack_process.push(num1 - num2);
      }
      else if (operation == '*')
      {
        if (isMultiplicationOverflow(num1, num2))
        {
          throw std::logic_error("Overflow during multiplication");
        }
        stack_process.push(num1 * num2);
      }
      else if (operation == '/')
      {
        if (num2 == 0)
        {
          throw std::logic_error("Division by zero");
        }
        stack_process.push(num1 / num2);
      }
      else if (operation == '%')
      {
        if (num2 == 0)
        {
          throw std::logic_error("Division by zero");
        }
        long long res = num1 % num2;
        if (num1 < 0)
        {
          res = std::abs(num2) + res;
        }
        stack_process.push(res);
      }
    }
    queue_postfix.pop();
  }
  return stack_process.top();
}
