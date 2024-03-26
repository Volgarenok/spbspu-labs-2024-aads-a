#include "calculate.hpp"
#include <list.hpp>
#include "stack.hpp"

#include <iostream>
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
        const long long min = std::numeric_limits< long long >::min();
        if (stack.size() < 2)
        {
          long long rhs = stack.drop();
          long long lhs = stack.drop();
          if (it.front().symbol.operation.operation == '+')
          {
            if (std::numeric_limits< long long >::max() - lhs < rhs)
            {
              throw std::logic_error("Overflow");
            }
            lhs += rhs;
          }
          else if (it.front().symbol.operation.operation == '-')
          {
            if (rhs != 0 && lhs != 0)
            {
              if ((rhs == -1 || lhs == -1) && (rhs == min || lhs == min))
              {
                throw std::logic_error("Overflow");
              }
              bool same_sign = true;
              if (lhs / rhs == 0)
              {
                same_sign = (rhs / lhs) > 0 ? true : false;
              }
              else
              {
                same_sign = (lhs / rhs) > 0 ? true : false;
              }
              if (same_sign == true)
              {
                if (std::numeric_limits< long long >::max() - std::abs(rhs) < lhs)
                {
                  throw std::logic_error("Overflow");
                }
              }
            }
            lhs -= rhs;
          }
          else if (it.front().symbol.operation.operation == '*')
          {
            if (rhs != 0 && lhs != 0)
            {
              if ((rhs == -1 || lhs == -1) && (rhs == min || lhs == min))
              {
                throw std::logic_error("Overflow");
              }
              else if (std::numeric_limits< long long >::max() / rhs < lhs)
              {
                throw std::logic_error("Overflow");
              }
            }
            lhs *= rhs;
          }
          else if (it.front().symbol.operation.operation == '/')
          {
            if ((rhs == -1 || lhs == -1) && (rhs == min || lhs == min))
            {
              throw std::logic_error("Overflow");
            }
            lhs /= rhs;
          }
          else if (it.front().symbol.operation.operation == '%')
          {
            lhs %= rhs;
          }
          else
          {
            throw std::logic_error("Incorrect operation");
          }
          stack.push(lhs);
          it.drop();
        }
        else
        {
          throw std::logic_error("Not enough operands");
        }
      }
    }
    if (!stack.empty())
    {
      result.push_back(stack.drop());
    }
  }
}
