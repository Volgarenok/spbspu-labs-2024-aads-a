#include "calculateProc.hpp"

#include <stdexcept>
#include <iostream>

#include "stack.hpp"

long long calcExp(long long first, long long second, char operation) // need overflow checks
{
  long long rObj = 0;
  if (operation == '+') // fine
  {
    rObj = (first + second);
  }
  else if (operation == '-') // fine
  {
    rObj = (first - second);
  }
  else if (operation == '*') // fine
  {
    rObj = (first * second);
  }
  else if (operation == '/') // fine
  {
    rObj = (first / second);
  }
  else if (operation == '%') //fine
  {
    rObj = (first % second);
  }
  else
  {
    throw std::logic_error("Calculation error!");
  }
  return rObj;
}

void arakelyan::calculatePostfixQ(Queue< Queue< detail::ExpressionObj > > &qOfPostfixQs, Stack< long long > &answerQ)
{
  Queue< detail::ExpressionObj > curQ = qOfPostfixQs.front();
  qOfPostfixQs.pop();

  Stack< long long > stack;

  while (!curQ.empty())
  {
    detail::ExpressionObj obj = curQ.front();
    curQ.pop();

    if (obj.type_ == detail::token_t::operation)
    {
      if (stack.size() < 2)
      {
        throw std::logic_error("Invalid sequence of expressions!");
      }
      long long right = stack.top();
      stack.pop();
      long long left = stack.top();
      stack.pop();
      stack.push((calcExp(left, right, obj.val_.oper_)));
    }
    else if (obj.type_ == detail::token_t::operand)
    {
      stack.push(obj.val_.operand_);
    }
    else
    {
      throw std::invalid_argument("Invalid argument in postfix queue!");
    }
  }
  answerQ.push(stack.top());
}
