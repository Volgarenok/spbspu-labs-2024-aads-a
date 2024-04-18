#include "solvedata.hpp"

#include <limits>
#include <stdexcept>

#include "checkdata.hpp"
#include "stack.hpp"

long long int gladyshev::evaluatePostfix(Queue< std::string > postfix)
{
  Stack < long long int > operands;
  while (!postfix.empty())
  {
    std::string token = postfix.drop();
    if (isNumber(token))
    {
      operands.push(std::stoll(token));
    }
    else if (isOperator(token))
    {
      long long int right = operands.drop();
      long long int left = operands.drop();
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
          throw std::overflow_error("overflow detected");
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
          throw std::overflow_error("division by 0");
        }
        operands.push(left / right);
      }
      else if (token == "%")
      {
        if (right == 0)
        {
          throw std::overflow_error("division by 0");
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
