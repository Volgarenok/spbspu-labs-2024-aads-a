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
ull evaluatePostfix(const char* postfix)
{
  zakozhurnikova::Stack< ull > stack;
  while (*postfix)
  {
    char ch = *postfix;
    if (std::isdigit(ch))
    {
      std::string value;
      value.push_back(ch);
      while (std::isdigit(*postfix))
      {
        ++postfix;
        value.push_back(*postfix);
      }
      stack.push(std::stoll(value));
    }
    else
    {
      ull second = stack.top();
      stack.drop();
      ull first = stack.top();
      stack.drop();
      stack.push(calculate(first, second, ch));
    }
    ++postfix;
  }
  ull result = stack.top();
  stack.drop();
  if (!stack.empty())
  {
    throw std::logic_error("Too much numbers!");
  }
  return result;
}

zakozhurnikova::Queue< ull >& evaluatePostfix(zakozhurnikova::Queue< ull >& result, zakozhurnikova::Queue< std::string >& queue)
{
  while (!queue.empty())
  {
    const char* postfix = queue.top().c_str();
    result.push(evaluatePostfix(postfix));
    queue.drop();
  }
  return result;
}
