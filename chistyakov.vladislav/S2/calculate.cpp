#include "calculate.hpp"
#include "stack.hpp"

int chistyakov::calculate(Queue< std::string > & exp)
{
  Stack< int > stack;

  while (!exp.empty())
  {
    if (isdigit(exp.front()[0]))
    {
      stack.push(std::stol(exp.front()));
    }
    else
    {
      int secondNum = stack.top();
      stack.pop();
      int firstNum = stack.top();
      stack.pop();

      if (exp.front() == "+")
      {
        stack.push(firstNum + secondNum);
      }
      else if (exp.front() == "-")
      {
        stack.push(firstNum - secondNum);
      }
      else if (exp.front() == "*")
      {
        stack.push(firstNum * secondNum);
      }
      else if (exp.front() == "/")
      {
        stack.push(firstNum / secondNum);
      }
      else if (exp.front() == "%")
      {
        stack.push(firstNum % secondNum);
      }
    }

    exp.pop();
  }

  return stack.top();
}

