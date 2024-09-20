#include "input_expressions.hpp"
#include <string>

static bool isMathOperation(char symbol)
{
  bool is_math_operation = false;
  if (symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/' || symbol == '%')
  {
    is_math_operation = true;
  }
  return is_math_operation;
}

void lebedev::inputInfixExpression(Queue< Queue< InfixExpression > > & queueInfix, std::istream & input)
{
  input >> std::fixed >> std::noskipws;
  while (input)
  {
    char curr_symb = 0;
    std::string num_str = "";
    Queue< InfixExpression > curr_expression;
    while (input >> curr_symb)
    {
      if (curr_symb == '(')
      {
        curr_expression.push(InfixExpression(true));
      }
      else if (curr_symb == ')')
      {
        curr_expression.push(InfixExpression(false));
      }
      else if (isMathOperation(curr_symb))
      {
        curr_expression.push(InfixExpression(curr_symb));
      }
      else if (std::isdigit(curr_symb))
      {
        num_str += curr_symb;
      }
      else if (curr_symb == ' ' && num_str != "")
      {
        curr_expression.push(InfixExpression(std::stoll(num_str)));
        num_str = "";
      }
      else if (curr_symb == '\n')
      {
        if (num_str != "")
        {
          curr_expression.push(InfixExpression(std::stoll(num_str)));
          num_str = "";
        }
        if (!curr_expression.empty())
        {
          queueInfix.push(curr_expression);
        }
        break;
      }
    }
  }
  input >> std::skipws;
}
