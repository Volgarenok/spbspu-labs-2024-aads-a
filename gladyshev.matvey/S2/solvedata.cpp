#include "solvedata.hpp"

#include <limits>
#include <stdexcept>
#include <string>

#include "topostfix.hpp"

long long int gladyshev::evaluatePostfix(Queue< std::string >& postfix)
{
  Stack < long long int > operands;
  while (!postfix.empty())
  {
    std::string token = postfix.back();
    postfix.pop();
    try
    {
      long long int value = std::stoll(token);
      operands.push(value);
    }
    catch (...)
    {
      long long int right = operands.top();
      operands.pop();
      long long int left = operands.top();
      operands.pop();
      if (token == "+")
      {
        if (std::numeric_limits< long long int >::max() - left < right)
        {
          throw std::overflow_error("overflow detected");
        }
        operands.push(left + right);
      }
      else if (token == "-")
      {
        if (std::numeric_limits < long long int >::min() + left > right)
        {
          throw std::underflow_error("overflow detected");
        }
        operands.push(left - right);
      }
      else if (token == "*")
      {
        long long int calc = left * right;
        if ((left != 0) && (calc / left) != right)
        {
          throw std::overflow_error("overflow detected");
        }
        operands.push(left * right);
      }
      else if (token == "/")
      {
        if (right == 0)
        {
          throw std::logic_error("division by 0");
        }
        operands.push(left / right);
      }
      else if (token == "%")
      {
        if (right == 0)
        {
          throw std::logic_error("division by 0");
        }
        left %= right;
        if (left < 0)
        {
          left += right;
        }
        operands.push(left);
      }
    }
  }
  return operands.top();
}

void gladyshev::inputExpression(std::istream& input, Stack< long long int >& results)
{
  std::string in = "";
  std::string token = "";
  while (std::getline(input, in))
  {
    if (in == "")
    {
      continue;
    }
    Queue< std::string > queuecheck;
    for (size_t i = 0; i < in.length(); ++i)
    {
      token = "";
      while (i < in.length() && !std::isspace(in[i]))
      {
        token += in[i];
        ++i;
      }
      if (!token.empty())
      {
        queuecheck.push(token);
      }
    }
    Queue< std::string > postfix = infixToPostfix(queuecheck);
    long long int result = evaluatePostfix(postfix);
    results.push(result);
  }
}
