#include "evaluatePostfix.hpp"
#include <stdexcept>
#include "stack.hpp"
#include "queue.hpp"

int calculate(int first, int second, char operation)
{
  int result = 0;
  switch (operation)
  {
  case '+':
    result = first + second;
    break;
  case '-':
    result = first - second;
    break;
  case '*':
    result = first * second;
    break;
  case '/':
    if (second == 0)
    {
      throw std::logic_error("LOGIC_ERROR: Division by zero!");
    }
    result = first / second;
    break;
  case '%':
    if (second == 0)
    {
      throw std::logic_error("LOGIC_ERROR: Division by zero!");
    }
    result = first % second;
    break;
  default:
    throw std::logic_error("LOGIC_ERROR: Wrong operation!");
    break;
  }
  return result;
}

using ull = unsigned long long;
ull evaluatePostfix(const std::string& postfix)
{
  zakozhurnikova::Stack< ull > stack;
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
      stack.push(std::stoll(value));
    }
    else if (std::isspace(*it))
    {
      continue;
    }
    else
    {
      ull second = stack.top();
      stack.drop();
      if (stack.empty())
      {
        return second;
      }
      ull first = stack.top();
      stack.drop();
      stack.push(calculate(first, second, *it));
    }
  }
  ull result = stack.top();
  stack.drop();
  if (!stack.empty())
  {
    throw std::logic_error("Too much numbers!");
  }
  return result;
}

zakozhurnikova::Stack< ull >& evaluatePostfix(zakozhurnikova::Stack< ull >& result, zakozhurnikova::Queue< std::string >& queue)
{
  while (!queue.empty())
  {
    result.push(evaluatePostfix(queue.top()));
    queue.drop();
  }
  return result;
}
