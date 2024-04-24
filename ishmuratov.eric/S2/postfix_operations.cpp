#include "postfix_operations.hpp"
#include <limits>
#include <stdexcept>
#include "checks.hpp"

void ishmuratov::calculate_postfix(Queue< std::string > & result_queue, Stack< long long int > & operands)
{
  while (!result_queue.empty())
  {
    std::string temp = result_queue.drop();
    if (isdigit(temp[0]))
    {
      operands.push(std::stoll(temp));
    }
    else if (isOperator(temp))
    {
      long long int n2 = operands.drop();
      long long int n1 = operands.drop();
      long long int res = 0;
      long long int max_value = std::numeric_limits< long long int >::max();
      long long int min_value = std::numeric_limits< long long int >::min();

      if (temp == "+")
      {
        if (n1 > max_value - n2)
        {
          throw std::overflow_error("Sum overflow!");
        }
        res = n1 + n2;
      }
      else if (temp == "-")
      {
        if (n1 < min_value + n2)
        {
          throw std::underflow_error("Subtraction underflow!");
        }
        res = n1 - n2;
      }
      else if (temp == "*")
      {
        if (n1 > max_value / n2)
        {
          throw std::overflow_error("Multiplication overflow!");
        }
        else if (n1 < min_value / n2)
        {
          throw std::underflow_error("Multiplication underflow!");
        }
        res = n1 * n2;
      }
      else if (temp == "/")
      {
        if (n2 == 0)
        {
          throw std::logic_error("Division by 0!");
        }
        res = n1 / n2;
      }
      else if (temp == "%")
      {
        if (n2 == 0)
        {
          throw std::logic_error("Division by 0!");
        }
        res = n1 % n2;
        if (res < 0)
        {
          res += n2;
        }
      }
      operands.push(res);
    }
    else
    {
      throw std::invalid_argument("Unexpected token!");
    }
  }
}
