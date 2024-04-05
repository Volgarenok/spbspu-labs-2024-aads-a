#include "tokens.hpp"

baranov::Token::Token(const std::string & str)
{
  if (str.size() == 1)
  {
    char c = str[0];
    if (c == '(' || c == ')')
    {
      type = TokenType::BRACKET;
      value.bracket.type = (c == '(' ? BracketType::OPEN : BracketType::CLOSE);
    }
    else if (c == '+' || c == '-' || c == '*' || c == '/')
    {
      type = TokenType::OPERATION;
      switch (c)
      {
        case '+':
          value.operation.type = OperationType::ADDITION;
          break;
        case '-':
          value.operation.type = OperationType::SUBTRACTION;
          break;
        case '*':
          value.operation.type = OperationType::MULTIPLICATION;
          break;
        case '/':
          value.operation.type = OperationType::DIVISION;
          break;
      }
    }
    else
    {
      throw std::logic_error("Invalid token");
    }
  }
  else
  {
    type = TokenType::OPERAND;
    value.operand.value = std::stoull(str);
  }
}

