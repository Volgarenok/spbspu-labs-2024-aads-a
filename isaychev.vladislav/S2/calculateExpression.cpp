#include "calculateExpression.hpp"
#include <iostream>
#include <cctype>
#include <cstdlib>

long long int isaychev::calculateExpression(Queue< std::string > & postfExp)
{
  Stack< long long int > calcStack;
  while (!postfExp.empty())
  {
    long long int nums[2] = {};
    std::string s = postfExp.front();
    postfExp.pop();
    std::cout << s << "\n";
    if (s == "+")
    {
      for (int i = 0; i < 2; ++i)
      {
        nums[i] = calcStack.top();
        calcStack.pop();
      }
      calcStack.push(nums[0] + nums[1]);
    }
    else if (s == "-")
    {
      for (int i = 0; i < 2; ++i)
      {
        nums[i] = calcStack.top();
        calcStack.pop();
      }
      calcStack.push(nums[0] - nums[1]);
    }
    else if (s == "*")
    {
      for (int i = 0; i < 2; ++i)
      {
        nums[i] = calcStack.top();
        calcStack.pop();
      }
      calcStack.push(nums[0] * nums[1]);
    }
    else if (s == "/")
    {
      for (int i = 0; i < 2; ++i)
      {
        nums[i] = calcStack.top();
        calcStack.pop();
      }
      calcStack.push(nums[0] / nums[1]);
    }
    else if (s == "%")
    {
      for (int i = 0; i < 2; ++i)
      {
        nums[i] = calcStack.top();
        calcStack.pop();
      }
      calcStack.push(nums[0] % nums[1]);
    }
    else
    {
      calcStack.push(std::stoll(s, nullptr, 10));
    }
  }
  return calcStack.top();
}
