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
          long long lhs = stack.drop();
          long long rhs = stack.drop();
          if (std::numeric_limits< long long >::max() - lhs < rhs)
          {
            throw std::logic_error("Overflow");
          }
          lhs += rhs;
          stack.push(lhs);
          it.drop();
        }
        else if (it.front().symbol.operation.operation == '-')
        {
          long long lhs = stack.drop();
          long long rhs = stack.drop();
          if (rhs != 0 && lhs != 0)
          {
            bool same_sign = true;
            if (lhs / rhs == 0)
            {
              same_sign = (rhs / lhs) > 0 ? true : false;
            }
            else
            {
              same_sign = (lhs / rhs) > 0 ? true : false;
            }
            if (same_sign)
            {
              if (std::numeric_limits< long long >::max() - std::abs(rhs) < lhs)
              {
                throw std::logic_error("Overflow");
              }
            }
          }
          rhs -= lhs;
          stack.push(lhs);
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
