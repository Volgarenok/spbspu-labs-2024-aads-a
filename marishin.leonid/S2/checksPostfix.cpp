#include "checksPostfix.hpp"
#include <stdexcept>
#include <limits>
#include "stack.hpp"
#include "queue.hpp"
#include "input.hpp"

marishin::Stack< long long >& marishin::checksPostfix(Stack< long long >& result, Queue< std::string >& queue)
{
  while (!queue.empty())
  {
    result.push(checksPostfixIn(queue.top()));
    queue.drop();
  }
  return result;
}

long long checksPostfixIn(const std::string& postfix)
{
  using input_it_t = std::string::const_iterator;
  marishin::Stack< long long > stack;
  input_it_t it = postfix.cbegin();
  while (it != postfix.cend())
  {
    std::string str;
    it = marishin::input(it, postfix.cend(), str);
    try
    {
      stack.push(std::stoll(str));
    }
    catch (const std::invalid_argument &)
    {
      if (std::isspace(*it))
      {
        continue;
      }
      else
      {
        long long second = stack.top();
        stack.drop();
        if (stack.empty())
        {
          return second;
        }
        long long first = stack.top();
        stack.drop();
        stack.push(calculate(first, second, str));
      }
    }
  }
  long long result = stack.top();
  stack.drop();
  if (!stack.empty())
  {
    throw std::logic_error("Overflow!");
  }
  return result;
}

long long calculate(long long num1, long long num2, const std::string& operation)
{
  long long result = 0;
  long long maxLong = std::numeric_limits< long long >::max();
  long long minLong = std::numeric_limits< long long >::min();
  if (op == '+')
  {
    if (maxLong - num1 < num2)
    {
      throw std::out_of_range("Overflow!");
    }
    result = num1 + num2;
  }
  else if (op == '-')
  {
    if (minLong + num1 > num2)
    {
      throw std::out_of_range("Overflow!");
    }
    result = num1 - num2;
  }
  else if (op == '*')
  {
    result = num1 * num2;
    if (num2 != && result / num2 < num1)
    {
      throw std::out_of_range("Overflow!");
    }
    num1 *= num2;
  }
  else if (op == '/')
  {
    if (num2 == 0)
    {
      throw std::logic_error("Division by zero!");
    }
    if ((num1 == minLong) && (num2 == -1))
    {
      throw std::out_of_range("Overflow!");
    }
    result = num1 / num2;
  }
  else if (op == '%')
  {
    result = num1 % num2;
    if (result < 0)
    {
      result += num2;
    }
  }
  else
  {
    throw std::invalid_argument("Wrong operator!");
  }
  return result;
}
