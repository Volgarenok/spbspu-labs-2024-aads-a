#include "calculatePostfix.hpp"
#include <limits>
#include <stack.hpp>

void baranov::calculatePostfixes(Queue< Queue< Token > > & postfixes, Stack< long long int > & results)
{
  while (!postfixes.empty())
  {
    results.push(calculatePostfix(postfixes.top()));
    postfixes.pop();
  }
}

long long int baranov::calculatePostfix(Queue< Token > & exp)
{
  Stack< Token > stack;
  while (!exp.empty())
  {
    Token t = exp.top();
    exp.pop();
    if (t.getType() == TokenType::OPERAND)
    {
      stack.push(t);
    }
    else if (t.getType() == TokenType::OPERATION)
    {
      if (stack.size() < 2)
      {
        throw std::logic_error("Invalid postfix expression");
      }
      long long int a = stack.top().getValue().operand.getValue();
      stack.pop();
      long long int b = stack.top().getValue().operand.getValue();
      long long int result = 0;

      switch (t.getValue().operation.getType())
      {
        case OperationType::ADDITION:
          result = sum(b, a);
          break;
        case OperationType::SUBTRACTION:
          result = sum(b, -a);
          break;
        case OperationType::MULTIPLICATION:
          result = multiply(b, a);
          break;
        case OperationType::DIVISION:
          result = div(b, a);
          break;
        case OperationType::MODULATION:
          result = mod(b, a);
          break;
      }
      stack.pop();
      Token topush(result);
      stack.push(topush);
    }
    else
    {
      throw std::logic_error("Invalid postfix expression");
    }
  }
  if (stack.size() != 1 || stack.top().getType() != TokenType::OPERAND)
  {
    throw std::logic_error("Invalid postfix expression");
  }
  return stack.top().getValue().operand.getValue();
}

long long int baranov::sum(long long int a, long long int b)
{
  const long long int max = std::numeric_limits< long long int >::max();
  const long long int min = std::numeric_limits< long long int >::min();
  if (same_sign(a, b) && (a > 0))
  {
    if (max - a >= b)
    {
      return a + b;
    }
  }
  else if (same_sign(a, b) && (a < 0))
  {
    if (min - a <= b)
    {
      return a + b;
    }
  }
  else if (!same_sign(a, b))
  {
    return a + b;
  }
  throw std::overflow_error("Addition overflow");
}

long long int baranov::multiply(long long int a, long long int b)
{
  long long int result = a * b;
  if (b != 0 && result / b != a)
  {
    throw std::overflow_error("Mulptiplication overflow");
  }
  return result;
}

long long int baranov::div(long long int a, long long int b)
{
  long long int min = std::numeric_limits< long long int >::min();
  if (b == 0)
  {
    throw std::logic_error("Division by zero");
  }
  else if (a == min && b == -1)
  {
    throw std::overflow_error("Division overflow");
  }
  return a / b;
}

long long int baranov::mod(long long int a, long long int b)
{
  long long int result = a % b;
  return result >= 0 ? result : result + b;
}

int baranov::sign(long long int val)
{
  return (val > 0) ? 1 : ((val < 0) ? -1 : 0);
}

bool baranov::same_sign(long long int a, long long int b)
{
  return sign(a) * sign(b) > 0;
}

