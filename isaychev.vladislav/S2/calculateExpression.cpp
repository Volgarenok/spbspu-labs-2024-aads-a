#include "calculateExpression.hpp"
#include <iostream>
#include <cctype>
#include <cstdlib>

void placeOperands(isaychev::Stack< long long int > & s, long long int * n)
{
  for (int i = 0; i < 2; ++i)
  {
    n[i] = s.top();
    s.pop();
  }
}

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
      placeOperands(calcStack, nums);
      calcStack.push(nums[1] + nums[0]);
    }
    else if (s == "-")
    {
      placeOperands(calcStack, nums);
      calcStack.push(nums[1] - nums[0]);
    }
    else if (s == "*")
    {
      placeOperands(calcStack, nums);
      calcStack.push(nums[1] * nums[0]);
    }
    else if (s == "/")
    {
      placeOperands(calcStack, nums);
      calcStack.push(nums[1] / nums[0]);
    }
    else if (s == "%")
    {
      placeOperands(calcStack, nums);
      calcStack.push(nums[1] % nums[0]);
    }
    else
    {
      calcStack.push(std::stoll(s, nullptr, 10));
    }
  }
  return calcStack.top();
}
