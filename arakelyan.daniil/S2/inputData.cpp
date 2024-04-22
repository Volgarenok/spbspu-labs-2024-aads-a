#include "inputData.hpp"

#include <cstddef>
#include <iostream>
#include <string>

bool isOperation(const std::string line)
{
  return line == "+" || line == "-" || line == "/" || line == "*" || line == "%";
}

bool isBracket(const std::string line)
{
  return line == "(" || line == ")";
}

arakelyan::Queue< arakelyan::ExpressionObj > arakelyan::readDataInInfixForm(std::istream &input)
{
  Queue< ExpressionObj > someQ;
  Token token;
  token_t tokenType = token_t::undef;

  std::string exp;
  while (input)
  {
    input >> exp;
    try
    {
      long long expLl = std::stoll(exp);
      token = Token(expLl);
      tokenType = token_t::operand;
    }
    catch (...)
    {
      char expCh = exp[0];
      token = Token(expCh);
      if (isOperation(exp))
      {
        tokenType = token_t::operation;
      }
      else if (isBracket(exp))
      {
        tokenType = token_t::bracket;
      }
    }

    ExpressionObj expObj{token, tokenType};
    someQ.push(expObj);
    if (input.peek() == '\n')
    {
      break;
    }
  }

  return someQ;
}
