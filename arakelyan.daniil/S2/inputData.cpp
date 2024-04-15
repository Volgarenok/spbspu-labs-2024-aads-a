#include "inputData.hpp"
#include "token.hpp"

#include <cstddef>
#include <iostream>
#include <string>

void arakelyan::readDataInfixForm(std::istream &input, Queue< ExpressionObj > &someQ)
{
  Token token;
  token_t tokenType = token_t::smthk;

  std::string exp = "";
  while (input >> exp && exp != "\n")
  {
    try
    {
      long long expLl = std::stoll(exp);
      token = Token(expLl);
      tokenType = token_t::operand;
    }
    catch (...)
    {
      std::cerr << "not ll\n";
    }
    ExpressionObj expObj{token, tokenType};
    someQ.push(expObj);
  }
}
