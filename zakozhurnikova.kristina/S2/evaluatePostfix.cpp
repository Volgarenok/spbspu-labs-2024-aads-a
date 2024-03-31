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

int evaluatePostfix(zakozhurnikova::Queue< std::string >& queue)
{
  zakozhurnikova::Stack< int > stack;

//пока очередь не пуста, перемещаемся по ней на одну единицу
  while(!queue.empty())
  {
//    char ch = *postfix;
    std::string st = queue.top();
    if (std::isdigit(ch))
    {
      std::string value;
      value.push_back(ch);
      while (std::isdigit(*postfix))
      {
        ++postfix;
        value.push_back(*postfix);
      }
      stack.push(std::stoi(value));
    }
    else
    {
      int second = stack.top();
      stack.pop();
      int first = stack.top();
      stack.pop();
      stack.push(calculate(first, second, ch));
    }
    ++postfix;
  }

  int result = stack.top();
  stack.pop();
  if (!stack.empty())
  {
    throw std::logic_error("Too much numbers!");
  }
  return result;
}
