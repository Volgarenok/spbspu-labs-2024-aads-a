#include "calculate_expression.hpp"

#include <limits>
#include <stdexcept>
#include "stack.hpp"

long long lebedev::safePlus(long long a, long long b)
{
  constexpr long long max_ll = std::numeric_limits< long long >::max();
  constexpr long long min_ll = std::numeric_limits< long long >::min();
  if ((b >= 0 && (max_ll - b < a)) || (b < 0 && (min_ll - b > a)))
  {
    throw std::out_of_range("ERROR: Sum overflow");
  }
  return a + b;
}

long long lebedev::safeMinus(long long a, long long b)
{
  constexpr long long max_ll = std::numeric_limits< long long >::max();
  constexpr long long min_ll = std::numeric_limits< long long >::min();
  if ((b < 0 && (max_ll + b < a)) || (b >= 0 && (min_ll + b > a)))
  {
    throw std::out_of_range("ERROR: Substraction overflow");
  }
  return a - b;
}

long long lebedev::safeMult(long long a, long long b)
{
  constexpr long long max_ll = std::numeric_limits< long long >::max();
  constexpr long long min_ll = std::numeric_limits< long long >::min();
  if ((b != 0) && ((max_ll / b < a) || (min_ll / b > a)))
  {
    throw std::out_of_range("ERROR: Multiplication overflow");
  }
  return a * b;
}

long long lebedev::safeDiv(long long a, long long b)
{
  constexpr long long min_ll = std::numeric_limits< long long >::min();
  if (b == 0)
  {
    throw std::logic_error("ERROR: Division by zero");
  }
  else if (a == min_ll && b == -1)
  {
    throw std::out_of_range("ERROR: Division overflow");
  }
  return a / b;
}

long long lebedev::safeMod(long long a, long long b)
{
  if (b == 0)
  {
    throw std::logic_error("ERROR: Division by zero");
  }
  long long res = a % b;
  if (res >= 0)
  {
    return res;
  }
  else
  {
    return (res + b);
  }
}

long long lebedev::calculatePostfixExpr(Queue< PostfixExpression > & queue_postfix)
{
  Stack< long long > stack_processing;
  while (!queue_postfix.empty())
  {
    PostfixExpression curr_symbol = queue_postfix.front();
    queue_postfix.pop();
    if (curr_symbol.getType() == Symbol::operand)
    {
      stack_processing.push(curr_symbol.getOperand());
    }
    else if (curr_symbol.getType() == Symbol::operation)
    {
      if (stack_processing.empty())
      {
        throw std::logic_error("ERROR: No operands in stack");
      }
      long long b = stack_processing.top();
      stack_processing.pop();
      long long a = stack_processing.top();
      stack_processing.pop();
      switch (curr_symbol.getOperation())
      {
      case '+':
        stack_processing.push(safePlus(a, b));
        break;
      case '-':
        stack_processing.push(safeMinus(a, b));
        break;
      case '*':
        stack_processing.push(safeMult(a, b));
        break;
      case '/':
        stack_processing.push(safeDiv(a, b));
        break;
      case '%':
        stack_processing.push(safeMod(a, b));
        break;
      }
    }
    else if (curr_symbol.getType() == Symbol::bracket)
    {
      throw std::invalid_argument("ERROR: Bracket in Postfix expression");
    }
  }
  long long res = stack_processing.top();
  stack_processing.pop();
  return res;
}
