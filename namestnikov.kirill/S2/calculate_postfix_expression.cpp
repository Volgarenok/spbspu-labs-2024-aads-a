#include "calculate_postfix_expression.hpp"
#include <stdexcept>
#include <limits>
#include "queue.hpp"
#include "stack.hpp"
#include "data_types.hpp"

void calculateExpression(long long & num1, long long num2, char op)
{
  if (op == '+')
  {
    long long maxLong = std::numeric_limits< long long >::max();
    if (maxLong - num2 < num1)
    {
      throw std::out_of_range("Overflow error");
    }
    num1 += num2;
  }
  else if (op == '-')
  {
    long long minLong = std::numeric_limits< long long >::min();
    if (minLong + num1 > num1)
    {
      throw std::out_of_range("Overflow error");
    }
    num1 -= num2;
  }
  else if (op == '*')
  {
    long long maxLong = std::numeric_limits< long long >::max();
    if (maxLong / num1 < num1)
    {
      throw std::out_of_range("Overflow error");
    }
    num1 *= num2;
  }
  else if (op == '/')
  {
    if (num2 == 0)
    {
      throw std::logic_error("Division by zero error");
    }
    long long minLong = std::numeric_limits< long long >::min();
    if ((num1 == minLong) && (num2 == -1))
    {
      throw std::out_of_range("Overflow error");
    }
    num1 /= num2;
  }
  else if (op == '%')
  {
    (num1 % num2 < 0) ? num1 %= num2 + num2 : num1 %= num2;
  }
  else
  {
    throw std::invalid_argument("Wrong operator");
  }
}

long long namestnikov::calculatePostfixExpression(Queue< namestnikov::Key > & resultQueue)
{
  Stack< long long > operandsStack;
  while (!resultQueue.empty())
  {
    namestnikov::Key token = resultQueue.front();
    resultQueue.pop();
    if (token.type == namestnikov::PartType::OPERATION)
    {
      if (operandsStack.empty())
      {
        throw std::runtime_error("Stack is empty");
      }
      long long secondNum = operandsStack.top();
      operandsStack.pop();
      calculateExpression(operandsStack.top(), secondNum, token.value.operand);
    }
    else if (token.type == namestnikov::PartType::OPERAND)
    {
      operandsStack.push(token.value.operand);
    }
    else if ((token.type == namestnikov::PartType::OPEN_BRACKET) || (token.type == namestnikov::PartType::CLOSE_BRACKET))
    {
      throw std::invalid_argument("Wrong bracket");
    }
  }
  return operandsStack.top();
}
