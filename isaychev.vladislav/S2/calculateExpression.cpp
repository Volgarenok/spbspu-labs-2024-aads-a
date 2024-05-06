#include "calculateExpression.hpp"
#include <iostream>
#include <cctype>
#include <cstdlib>

long long int isaychev::calculateExpression(Queue< std::string > & postfExp)
{
  Stack< long long int > calcStack;
  long long int nums[2] = {};
  std::string s = "";
  while (!postfExp.empty())
  {
    s = postfExp.front();
    postfExp.pop();
    if (s == "+")
    {
      for (int i = 0; i < 2; ++i)
      {
        nums[i] = calcStack.top();
        calcStack.pop();
      }
      calcStack.push(nums[1] + nums[0]);
    }
    else if (s == "-")
    {
      for (int i = 0; i < 2; ++i)
      {
        nums[i] = calcStack.top();
        calcStack.pop();
      }
      calcStack.push(nums[1] - nums[0]);
    }
    else if (s == "*")
    {
      for (int i = 0; i < 2; ++i)
      {
        nums[i] = calcStack.top();
        calcStack.pop();
      }
      calcStack.push(nums[1] * nums[0]);
    }
    else if (s == "/")
    {
      for (int i = 0; i < 2; ++i)
      {
        nums[i] = calcStack.top();
        calcStack.pop();
      }
      calcStack.push(nums[1] / nums[0]);
    }
    else if (s == "%")
    {
      for (int i = 0; i < 2; ++i)
      {
        nums[i] = calcStack.top();
        calcStack.pop();
      }
      calcStack.push(nums[1] % nums[0]);
    }
    else
    {
      calcStack.push(std::stoll(s, nullptr, 10));
    }
  }
  return calcStack.top();
}
