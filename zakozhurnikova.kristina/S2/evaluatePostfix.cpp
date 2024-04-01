#include "evaluatePostfix.hpp"
#include <stdexcept>
#include <limits>
#include "stack.hpp"
#include "queue.hpp"

using ll = long long;
ll calculate(ll first, ll second, char operation)
{
  ll result = 0;
  switch (operation)
  {
  case '+':
  {
    ll maxNum = std::numeric_limits<ll>::max();
    if (maxNum - first < second)
    {
      throw std::out_of_range("Error: Addition overflow");
    }
    result = first + second;
    break;
  }
  case '-':
  {
    ll minNum = std::numeric_limits<ll>::min();
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
    ll minNum = std::numeric_limits<ll>::min();
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


ll evaluatePostfixPart(const std::string& postfix)
{
  zakozhurnikova::Stack< ll > stack;
  for(auto it = postfix.cbegin(); it != postfix.cend(); ++it)
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
      ll second = stack.top();
      stack.drop();
      if (stack.empty())
      {
        return second;
      }
      ll first = stack.top();
      stack.drop();
      stack.push(calculate(first, second, *it));
    }
  }
  ll result = stack.top();
  stack.drop();
  if (!stack.empty())
  {
    throw std::logic_error("Too much numbers!");
  }
  return result;
}

zakozhurnikova::Stack< ll >& zakozhurnikova::evaluatePostfix(zakozhurnikova::Stack< ll >& result, zakozhurnikova::Queue< std::string >& queue)
{
  while (!queue.empty())
  {
    result.push(evaluatePostfixPart(queue.top()));
    queue.drop();
  }
  return result;
}
