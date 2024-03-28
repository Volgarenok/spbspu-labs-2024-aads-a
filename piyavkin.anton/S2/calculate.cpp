#include "calculate.hpp"
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
        const long long min = std::numeric_limits< long long >::min();
        const size_t numbers_operand = 2;
        if (stack.size() >= numbers_operand)
        {
          long long rhs = stack.drop();
          long long lhs = stack.drop();
          if (it.front().symbol.operation.operation == '+')
          {
            if (std::numeric_limits< long long >::max() - lhs < rhs)
            {
              throw std::logic_error("Addition Overflow");
            }
            lhs += rhs;
          }
          else if (it.front().symbol.operation.operation == '-')
          {
            if (rhs != 0 && lhs != 0)
            {
              if ((rhs == -1 || lhs == -1) && (rhs == min || lhs == min))
              {
                throw std::logic_error("Subtraction overflow");
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
                  throw std::logic_error("Subtraction overflow");
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
                throw std::logic_error("Overflow when multiplying by -1");
              }
              else if (std::numeric_limits< long long >::max() / rhs < lhs)
              {
                throw std::logic_error("Multiplication overflow");
              }
            }
            lhs *= rhs;
          }
          else if (it.front().symbol.operation.operation == '/')
          {
            if (rhs == 0)
            {
              throw std::logic_error("Division by 0");
            }
            else if (rhs == -1 && lhs == min)
            {
              throw std::logic_error("Division overflow");
            }
            lhs /= rhs;
          }
          else if (it.front().symbol.operation.operation == '%')
          {
            if (rhs == 0)
            {
              throw std::logic_error("Taking the remainder to 0");
            }
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
    if (stack.size() == 1)
    {
      result.push_back(stack.drop());
    }
    else
    {
      if (!stack.empty())
      {
        throw std::logic_error("There is no clear answer");
      }
    }
  }
}
