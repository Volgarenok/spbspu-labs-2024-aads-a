#include "topostfix.hpp"

#include <map>
#include <stdexcept>
#include "stack.hpp"
#include "checkdata.hpp"

gladyshev::Queue< std::string > gladyshev::infixToPostfix(Queue< std::string > expression)
{
  Stack< std::string > ops;
  Queue< std::string > output;
  std::string token = "";

  std::map< std::string, int > quality =
  {
    {"+", 1},
    {"-", 1},
    {"*", 2},
    {"/", 2},
    {"%", 2}
  };
  while(!expression.empty())
  {
    std::string value = expression.drop();
    if (isNumber(value))
    {
      output.push(value);
    }
    else if (isOperator(value))
    {
      while (!ops.empty() && isOperator(ops.top()) && quality[ops.top()] >= quality[value])
      {
        output.push(ops.drop());
      }
      ops.push(value);
    }
    else if (value == "(")
    {
      ops.push(value);
    }
    else if (value == ")")
    {
      while (ops.top() != "(")
      {
        if (!isOperator(ops.top()))
        {
          throw std::logic_error("what is that");
        }
        output.push(ops.drop());
      }
      ops.drop();
    }
    else
    {
      throw std::logic_error("what is that");
    }
  }
  if (!ops.empty())
  {
    output.push(ops.drop());
  }
  return output;
}
