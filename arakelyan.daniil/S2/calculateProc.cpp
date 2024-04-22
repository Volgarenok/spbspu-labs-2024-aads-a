#include "calculateProc.hpp"
#include "stack.hpp"

#include <stdexcept>
#include <iostream>

long long calcExp(long long first, long long second, char operation)
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

void arakelyan::calculatePostfixQ(Queue< Queue< ExpressionObj > > &qOfPostfixQs, Queue< long long > &answerQ)
{
  Queue< ExpressionObj > curQ = qOfPostfixQs.front();
  qOfPostfixQs.pop();

  if (curQ.empty())
  {
    // throw std::logic_error("empty q!");
    return;
  }
  std::cout << "start calculate\n";

  Stack< long long > stack;

  while (!curQ.empty())
  {
    ExpressionObj obj = curQ.front();
    curQ.pop();

    if (obj.type_ == token_t::operation)
    {
      if (stack.size() < 2)
      {
        throw std::logic_error("Invalid sequence of expressions!");
      }
      long long sec = stack.top();
      stack.pop();
      long long first = stack.top();
      stack.pop();
      stack.push((calcExp(first, sec, obj.val_.oper_)));
    }
    else if (obj.type_ == token_t::operand)
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
