#include "input_expression.hpp"
#include <stdexcept>
#include <string>

bool isDigit(char c)
{
  return (c >= '0' && c <= '9');
}

bool isArithmetic(char c)
{
  return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%');
}

void lopatina::inputExpression(std::istream & in, Queue< InfixType > & queue_source)
{
  char c = 0;
  std::string num_str = "";
  in >> std::noskipws;
  while (in >> c)
  {
    if (c == '\n')
    {
      if (!num_str.empty())
      {
        long long num = std::stoll(num_str);
        InfixType elem{num, TypeName::OPERAND};
        queue_source.push(elem);
      }
      in >> std::skipws;
      return;
    }
    if (isDigit(c))
    {
      num_str += c;
    }
    else if (c == ' ')
    {
      if (!num_str.empty())
      {
        long long num = std::stoll(num_str);
        InfixType elem{num, TypeName::OPERAND};
        queue_source.push(elem);
        num_str = "";
      }
    }
    else if (c == '(')
    {
      InfixType elem{c, TypeName::OPEN_BRACKET};
      queue_source.push(elem);
    }
    else if (c == ')')
    {
      InfixType elem{c, TypeName::CLOSE_BRACKET};
      queue_source.push(elem);
    }
    else if (isArithmetic(c))
    {
      InfixType elem{c, TypeName::OPERATION};
      queue_source.push(elem);
    }
    else
    {
      in >> std::skipws;
      throw std::invalid_argument("Invalid expression element");
    }
  }
}
