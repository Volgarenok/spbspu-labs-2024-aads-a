#include "postfixFromInfix.hpp"
#include <cstddef>
#include <stdexcept>
#include "stack.hpp"
#include "tokenType.hpp"

void pushUntilOpen(grechishnikov::Queue< std::string >& res, grechishnikov::Stack< std::string >& from)
{
  while (from.top() != "(")
  {
    res.push(from.top());
    from.pop();
    if (from.size() == 0)
    {
      throw std::logic_error("Mathematical expression is incorrect");
    }
  }
  from.pop();
}

bool higherPriority(std::string first, std::string second)
{
  return (first == "(" || second == "(") or ((second == "*" || second == "/") && (first == "+" || first == "-"));
}

grechishnikov::Queue< std::string > grechishnikov::postfixFromInfix(const Queue< std::string >& infix)
{
  Queue< std::string > temp = infix;
  Queue< std::string > res;
  Stack< std::string > stack;
  while (!temp.empty())
  {
    if (isOperand(temp.top()))
    {
      res.push(temp.top());
      temp.pop();
    }
    else if (isOperator(temp.top()) || temp.top() == "(")
    {
      if (!stack.empty())
      {
        if (!higherPriority(stack.top(), temp.top()))
        {
          res.push(stack.top());
          stack.pop();
        }
      }
      stack.push(temp.top());
      temp.pop();
    }
    else if (temp.top() == ")")
    {
      temp.pop();
      pushUntilOpen(res, stack);
    }
  }
  while (stack.size() != 0)
  {
    res.push(stack.top());
    stack.pop();
  }
  return res;
}

