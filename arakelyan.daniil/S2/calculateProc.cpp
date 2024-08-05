#include "calculateProc.hpp"

#include <stdexcept>
#include <limits>

#include "expressionObject.hpp"
#include "stack.hpp"

long long calcExp(long long first, long long second, arakelyan::ExpressionObj obj)
{
  constexpr long long maxVal = std::numeric_limits< long long >::max();
  constexpr long long minVal = std::numeric_limits< long long >::min();
  long long rObj = 0;
  char operation = obj.getOper();
  if (operation == '+')
  {
    if (first > (maxVal - second))
    {
      throw std::overflow_error("Addition overflow error!");
    }
    rObj = (first + second);
  }
  else if (operation == '-')
  {
    if (first - second < minVal)
    {
      throw std::underflow_error("Sub underflow error");
    }
    rObj = (first - second);
  }
  else if (operation == '*')
  {
    if (first != 0 && (second > (maxVal / first) || second < (minVal / first)))
    {
      throw std::overflow_error("Multiplication overflow error!");
    }
    rObj = (first * second);
  }
  else if (operation == '/')
  {
    if (second == 0)
    {
      throw std::logic_error("Division by zero!");
    }
    else if (first == minVal && second == -1)
    {
      throw std::overflow_error("Division overflow!");
    }
    rObj = (first / second);
  }
  else if (operation == '%')
  {
    if (second == 0)
    {
      throw std::logic_error("Division by zero!");
    }
    rObj = (first % second);
    if (rObj < 0)
    {
      rObj += second;
    }
  }
  else
  {
    throw std::logic_error("Calculation error!");
  }
  return rObj;
}

void arakelyan::calculatePostfixQ(Queue< Queue< ExpressionObj > > &qOfPostfixQs, Stack< long long > &answerQ)
{
  Queue< ExpressionObj > curQ = qOfPostfixQs.front();
  qOfPostfixQs.pop();

  Stack< long long > stack;

  while (!curQ.empty())
  {
    ExpressionObj obj = curQ.front();
    curQ.pop();

    if (obj.getType() == token_t::operation)
    {
      if (stack.size() < 2)
      {
        throw std::logic_error("Invalid sequence of expressions!");
      }
      long long right = stack.top();
      stack.pop();
      long long left = stack.top();
      stack.pop();
      long long res = calcExp(left, right, obj);
      stack.push(res);
    }
    else if (obj.getType() == token_t::operand)
    {
      stack.push(obj.getNumber());
    }
    else
    {
      throw std::invalid_argument("Invalid argument in postfix queue!");
    }
  }
  answerQ.push(stack.top());
}
