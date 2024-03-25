#include "calculate.hpp"
#include <list.hpp>
#include "stack.hpp"

void piyavkin::calculate(List< Queue< Postfix > >& postfix, List< long long >& result)
{
  Stack< long long > stack;
  for (auto it: postfix)
  {
    while (!it.empty())
    {
      if (it.front().type == detail::operand)
      {
        stack.push(it.drop().symbol.operand.number);
      }
      else
      {
        if (it.front().symbol.operation.operation == '+')
        {
          long long temp = stack.drop() + stack.drop();
          stack.push(temp);
          it.drop();
        }
        else if (it.front().symbol.operation.operation == '-')
        {
          long long temp = stack.drop() - stack.drop();
          stack.push(-temp);
          it.drop();
        }
        else if (it.front().symbol.operation.operation == '*')
        {
          long long temp = stack.drop() * stack.drop();
          stack.push(temp);
          it.drop();
        }
        else if (it.front().symbol.operation.operation == '/')
        {
          long long div = stack.drop();
          long long temp = stack.drop() / div;
          stack.push(temp);
          it.drop();
        }
        else if (it.front().symbol.operation.operation == '%')
        {
          long long div = stack.drop();
          long long temp = stack.drop() % div;
          stack.push(temp);
          it.drop();
        }
        else
        {
          throw std::logic_error("Incorrect operation");
        }
      }
    }
    if (!stack.empty())
    {
      result.push_back(stack.drop());
    }
  }
}