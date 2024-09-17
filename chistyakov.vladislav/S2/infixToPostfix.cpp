#include "infixToPostfix.hpp"
#include "queue.hpp"
#include "stack.hpp"
#include <iostream>

bool chistyakov::prioritet(const std::string fstOp, const std::string sndOp)
{
  return (fstOp == "*" || fstOp == "/" || fstOp == "%") && (sndOp == "+" || sndOp == "-");
}

void chistyakov::infixToPostfix(Queue< std::string > & queue, Queue< std::string > & exp)
{
  Stack< std::string > stack;
  std::string element;

  while (!exp.empty())
  {
    element = exp.front();

    if (std::isdigit(element[0]))
    {
      queue.push(element);
    }
    else
    {
      if (element == "(")
      {
        stack.push(element);
      }
      else if (element == ")")
      {
        while (stack.top() != "(")
        {
          queue.push(stack.top());
          stack.pop();
        }
        stack.pop();
      }
      else
      {
        if (stack.empty() || stack.top() == "(")
        {
          stack.push(element);
        }
        else if (prioritet(element, stack.top()))
        {
          stack.push(element);
        }
        else
        {
          bool flag = true;

          while (flag && !stack.empty())
          {
            queue.push(stack.top());
            if (!prioritet(element, stack.top()) || stack.top() == "(" || stack.top() == element)
            {
              flag = false;
            }
            //std::cout << element << " " << stack.top() << " " << flag << "\n";
            stack.pop();
          }

          stack.push(element);
        }
      }
    }

    exp.pop();
  }
  while (!stack.empty())
  {
    queue.push(stack.top());
    stack.pop();
  }
}
