#include "evaluatePostfix.hpp"
#include <stdexcept>
#include <limits>
#include "stack.hpp"
#include "queue.hpp"
#include "readWord.hpp"

long long calculate(long long first, long long second, const std::string& operation)
{
  long long result = 0;
  if (operation == "+")
  {
    long long maxNum = std::numeric_limits< long long >::max();
    if (maxNum - first < second)
    {
      throw std::out_of_range("Error: Addition overflow");
    }
    result = first + second;
  }
  else if (operation == "-")
  {
    long long minNum = std::numeric_limits< long long >::min();
    if (minNum + first > second)
    {
      throw std::out_of_range("Error: Subtraction overflow");
    }
    result = first - second;
  }
  else if (operation == "*")
  {
    result = first * second;
    if (second != 0 && result / second != first)
    {
      throw std::out_of_range("Error: Mulptiplication overflow");
    }
  }
  else if (operation == "/")
  {
    long long minNum = std::numeric_limits< long long >::min();
    if (second == 0)
    {
      throw std::logic_error("Error: Division by zero");
    }
    if (first == minNum && second == -1)
    {
      throw std::out_of_range("Error: Division overflow");
    }
    result = first / second;
  }
  else if (operation == "%")
  {
    result = first % second;
    if (result < 0)
    {
      result += second;
    }
  }
  else
  {
    throw std::logic_error("Error: Wrong operation");
  }
  return result;
}

using c_iterator_t = std::string::const_iterator;

long long evaluatePostfixPart(const std::string& postfix)
{
  zakozhurnikova::Stack< long long > stack;
  c_iterator_t it = postfix.cbegin();
  while (it != postfix.cend())
  {
    std::string sub;
    it = zakozhurnikova::readWord(it, postfix.cend(), sub);
    try
    {
      stack.push(std::stoll(sub));
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
        stack.push(calculate(first, second, sub));
      }
    }
  }

  long long result = stack.top();
  stack.drop();
  if (!stack.empty())
  {
    throw std::logic_error("Too much numbers!");
  }
  return result;
}

namespace zak = zakozhurnikova;
zak::Stack< long long >& zak::evaluatePostfix(Stack< long long >& result, Queue< std::string >& queue)
{
  while (!queue.empty())
  {
    result.push(evaluatePostfixPart(queue.top()));
    queue.drop();
  }
  return result;
}
