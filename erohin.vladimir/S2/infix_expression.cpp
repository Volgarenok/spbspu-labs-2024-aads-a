#include "infix_expression.hpp"
#include <iostream>
#include <string>
#include <stdexcept>

std::istream & erohin::inputInfixExpression(std::istream & input, infix_expression & inf_expr)
{
  std::istream::sentry sentry(input);
  if (!sentry)
  {
    return input;
  }
  std::string string_token;
  token_identifier_t temp_id = token_identifier_t::OPERAND_TYPE;
  token_t temp_token{ Operand() };
  while (input >> string_token)
  {
    try
    {
      temp_token.operand = Operand(stoll(string_token));
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
        throw std::logic_error("Unidentified token");
      }
    }
    inf_expr.push(Token{ temp_id, temp_token });
  }
  return input;
}

