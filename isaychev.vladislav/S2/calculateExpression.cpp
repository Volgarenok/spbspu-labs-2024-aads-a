#include "calculateExpression.hpp"
#include <cctype>
#include <cstdlib>
#include <limits>

void placeOperands(isaychev::Stack< isaychev::Operand > & s, isaychev::Operand n[])
{
  for (int i = 0; i < 2; ++i)
  {
    n[i] = s.top();
    s.pop();
  }
}

long long int isaychev::calculateExpression(Queue< Token > & postfExp)
{
  Stack< Operand > calcStack;
  Operand ops[2] = {};
//  long long int max = std::numeric_limits< long long int >::max();
  //std::string s = "";

  while (!postfExp.empty())
  {
    Token t = postfExp.front();
    postfExp.pop();
    if (t.type == TokenType::OPERATION)
    {
      placeOperands(calcStack, ops);
      calcStack.push(t.value.operation(ops[1], ops[0]));
    }
    else if (t.type == TokenType::OPERAND)
    {
      calcStack.push(t.value.operand);
    }
  }
  return calcStack.top().get_operand();

/*  while (!postfExp.empty())
  {
    s = postfExp.front();
    postfExp.pop();
    if (s == "+")
    {
      placeOperands(calcStack, nums);
      if (max - nums[1] < nums[0])
      {
        throw std::overflow_error("addition overflow");
      }
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
      if (nums[0] != 0 && (max / std::abs(nums[0]) < std::abs(nums[1])))
      {
        throw std::overflow_error("multiplication overflow");
      }
      calcStack.push(nums[1] * nums[0]);
    }
    else if (s == "/")
    {
      placeOperands(calcStack, nums);
      if (nums[0] == 0)
      {
        throw std::logic_error("division by zero");
      }
      calcStack.push(nums[1] / nums[0]);
    }
    else if (s == "%")
    {
      placeOperands(calcStack, nums);
      if (nums[0] == 0)
      {
        throw std::logic_error("mod zero");
      }
      long long int n = nums[1] % nums[0];
      if (n < 0)
      {
        n += nums[0];
      }
      calcStack.push(n);
    }
    else
    {
      calcStack.push(std::stoll(s, nullptr, 10));
    }
  }
  return calcStack.top();*/
}
