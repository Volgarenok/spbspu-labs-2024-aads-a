#include "evaluatePostfix.hpp"
#include <stdexcept>
#include <limits>
#include "stack.hpp"
#include "queue.hpp"

long long calculate(long long first, long long second, char operation)
{
  long long result = 0;
  switch (operation)
  {
  case '+':
  {
    long long maxNum = std::numeric_limits< long long >::max();
    if (maxNum - first < second)
    {
      throw std::out_of_range("Error: Addition overflow");
    }
    result = first + second;
    break;
  }
  case '-':
  {
    long long minNum = std::numeric_limits< long long >::min();
    if (minNum + first > second)
    {
      throw std::out_of_range("Error: Subtraction overflow");
    }
    result = first - second;
    break;
  }
  case '*':
    result = first * second;
    if (second != 0 && result / second != first)
    {
      throw std::out_of_range("Error: Mulptiplication overflow");
    }
    break;
  case '/':
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
    break;
  }
  case '%':
  {
    result = first % second;
    if (result < 0)
    {
      result += second;
    }
    break;
  }
  default:
    throw std::logic_error("Error: Wrong operation");
  }
  return result;
}


long long evaluatePostfixPart(const std::string& postfix)
{
  zakozhurnikova::Stack< long long > stack;
  for (auto it = postfix.cbegin(); it != postfix.cend(); ++it)
  {
    if (std::isdigit(*it))
    {
      auto cpy = it;
      std::string value;
      value.push_back(*cpy);
      while (std::isdigit(*cpy))
      {
        ++cpy;
        value.push_back(*cpy);
      }
      it = --cpy;
      stack.push(std::stoll(value));
    }
    else if (std::isspace(*it))
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
      stack.push(calculate(first, second, *it));
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
