#include "calculatePostfix.hpp"
#include "operations.hpp"
#include <stdexcept>

void chernov::convertToValues(Queue< queue >& postfix_queue, stack& result_stack)
{
  std::string token = "";
  while (!postfix_queue.empty())
  {
    queue temp_postfix = postfix_queue.back();
    postfix_queue.pop();
    stack interim_stack;
    while (!temp_postfix.empty())
    {
      token = "";
      token = temp_postfix.back();
      temp_postfix.pop();
      try
      {
        interim_stack.push(std::stoll(token));
      }
      catch (...)
      {
        long long int second = interim_stack.top();
        interim_stack.pop();
        long long int first = interim_stack.top();
        interim_stack.pop();
        long long int result = 0;
        if (token == "+")
        {
          if (std::numeric_limits< long long int >::max() - second <= first)
          {
            throw std::overflow_error("The number exceeded the limit");
          }
          result = first + second;
          interim_stack.push(result);
        }
        else if (token == "-")
        {
          if (std::numeric_limits< long long int >::min() + second >= first)
          {
            throw std::overflow_error("The number exceeded the limit");
          }
          result = first - second;
          interim_stack.push(result);
        }
        else if (token == "*")
        {
          result = first * second;
          interim_stack.push(result);
        }
        else if (token == "/")
        {
          if (second == 0)
          {
            throw std::logic_error("division by 0");
          }
          if ((first == std::numeric_limits< long long int >::min()) && (second == -1))
          {
            throw std::overflow_error("The number exceeded the limit");
          }
          result = first / second;
          interim_stack.push(result);
        }
        else
        {
          if (second == 0)
          {
            throw std::logic_error("division by 0");
          }
          result = first % second;
          interim_stack.push(result);
        }
      }
    }
    long long int value = interim_stack.top();
    interim_stack.pop();
    result_stack.push(value);
  }
}
