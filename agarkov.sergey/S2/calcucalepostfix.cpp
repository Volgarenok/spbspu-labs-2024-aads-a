#include "calcucalepostfix.hpp"
#include <string>
#include "queue.hpp"
#include "stack.hpp"
#include "arithmetic.hpp"

long long agarkov::calculatePostfix(agarkov::Queue< std::string >& postfixQueue)
{
  agarkov::Stack< long long > stack;
  while (!postfixQueue.isEmpty())
  {
    std::string token = postfixQueue.get();
    postfixQueue.pop();
    if (std::isdigit(token[0]))
    {
      stack.push(std::stoll(token));
    }
    else
    {
      long long operand2 = stack.get();
      stack.pop();
      long long operand1 = stack.get();
      stack.pop();
      long long result;
      if (token == "+")
      {
        result = agarkov::sum(operand1, operand2);
      }
      else if (token == "-")
      {
        result = agarkov::subtract(operand1, operand2);
      }
      else if (token == "*")
      {
        result = agarkov::multiply(operand1, operand2);
      }
      else if (token == "/")
      {
        result = agarkov::division(operand1, operand2);
      }
      else if (token == "%")
      {
        result = agarkov::remaind(operand1, operand2);
      }
      stack.push(result);
    }
  }
  return stack.get();
}
