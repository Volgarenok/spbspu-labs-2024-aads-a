#include "topostfix.hpp"

#include <stdexcept>

#include "stack.hpp"
#include "checkdata.hpp"

gladyshev::Queue< std::string > gladyshev::infixToPostfix(Queue< std::string >& expression)
{
  Stack< std::string > ops;
  Queue< std::string > output;
  std::string token = "";
  while (!expression.empty())
  {
    std::string value = expression.back();
    expression.pop();
    try
    {
      std::stoll(value);
      output.push(value);
    }
    catch (...)
    {
      if (isOperator(value))
      {
        while (!ops.empty() && checkQuality(ops.top(), value))
        {
          output.push(ops.top());
          ops.pop();
        }
        ops.push(value);
      }
      else if (value == "(")
      {
        ops.push(value);
      }
      else if (value == ")")
      {
        while (!ops.empty() && ops.top() != "(")
        {
          output.push(ops.top());
          ops.pop();
        }
        ops.pop();
      }
      else
      {
        throw std::logic_error("what is that");
      }
    }
  }
  while (!ops.empty())
  {
    if (ops.top() == "(")
    {
      throw std::logic_error("bad bracket");
    }
    output.push(ops.top());
    ops.pop();
  }
  return output;
}
