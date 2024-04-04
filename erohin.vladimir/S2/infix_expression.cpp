#include "infix_expression.hpp"
#include <iostream>
#include <string>
#include <stdexcept>

void erohin::inputInfixExpression(std::istream & input, expression_t & inf_expr)
{
  std::string string_token;
  token_identifier_t temp_id = token_identifier_t::OPERAND_TYPE;
  token_t temp_token{ Operand() };
  bool isUnidentifiedTokenFound = false;
  input >> string_token;
  while (input)
  {
    try
    {
      temp_token.operand = Operand(std::stoll(string_token));
      temp_id = token_identifier_t::OPERAND_TYPE;
    }
    catch (const std::invalid_argument &)
    {
      if (string_token == "(")
      {
        temp_token.bracket = Bracket{ bracket_t::OPEN_BRACKET };
        temp_id = token_identifier_t::BRACKET_TYPE;
      }
      else if (string_token == ")")
      {
        temp_token.bracket = Bracket{ bracket_t::CLOSE_BRACKET };
        temp_id = token_identifier_t::BRACKET_TYPE;
      }
      else if (string_token.length() == 1)
      {
        temp_token.operation = Operator(string_token[0]);
        temp_id = token_identifier_t::OPERATOR_TYPE;
      }
      else
      {
        throw;
      }
    }
    inf_expr.push(Token{ temp_id, temp_token });
    if (input.peek() == '\n')
    {
      break;
    }
    input >> string_token;
  }
  if (isUnidentifiedTokenFound)
  {
    throw std::logic_error("Unidentified token is found");
  }
}
