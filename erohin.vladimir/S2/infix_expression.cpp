#include "infix_expression.hpp"
#include <iostream>
#include <string>
#include <cstring>
#include <stdexcept>

void erohin::inputInfixExpression(std::istream & input, expression_t & inf_expr)
{
  std::string line;
  std::getline(input, line);
  if (!input || line.empty())
  {
    return;
  }
  char * string_token = std::strtok(const_cast< char * >(line.data()), " ");
  token_identifier_t temp_id = token_identifier_t::OPERAND_TYPE;
  token_t temp_token{ Operand() };
  bool isUnidentifiedTokenFound = false;
  while (string_token)
  {
    try
    {
      temp_token.operand = Operand(std::stoll(std::string(string_token)));
      temp_id = token_identifier_t::OPERAND_TYPE;
    }
    catch (const std::invalid_argument &)
    {
      if (string_token[1] == '\0' && string_token[0] == '(')
      {
        temp_token.bracket = Bracket{ bracket_t::OPEN_BRACKET };
        temp_id = token_identifier_t::BRACKET_TYPE;
      }
      else if (string_token[1] == '\0' && string_token[0] == ')')
      {
        temp_token.bracket = Bracket{ bracket_t::CLOSE_BRACKET };
        temp_id = token_identifier_t::BRACKET_TYPE;
      }
      else if (string_token[1] == '\0')
      {
        temp_token.operation = Operator(string_token[0]);
        temp_id = token_identifier_t::OPERATOR_TYPE;
      }
      else
      {
        isUnidentifiedTokenFound = true;
      }
    }
    inf_expr.push(Token{ temp_id, temp_token });
    string_token = std::strtok(nullptr, " ");
  }
  if (isUnidentifiedTokenFound)
  {
    throw std::logic_error("Unidentified token is found");
  }
}
