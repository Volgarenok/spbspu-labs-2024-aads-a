#include "tokens.hpp"

baranov::Token::Token(const std::string & str)
{
  if (str.size() == 1 && !isdigit(str[0]))
  {
    char c = str[0];
    if (c == '(' || c == ')')
    {
      type = TokenType::BRACKET;
      value.bracket.type = (c == '(' ? BracketType::OPEN : BracketType::CLOSE);
    }
    else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%')
    {
      type = TokenType::OPERATION;
      switch (c)
      {
        case '+':
          value.operation.type = OperationType::ADDITION;
          value.operation.priority = 2;
          break;
        case '-':
          value.operation.type = OperationType::SUBTRACTION;
          value.operation.priority = 2;
          break;
        case '*':
          value.operation.type = OperationType::MULTIPLICATION;
          value.operation.priority = 1;
          break;
        case '/':
          value.operation.type = OperationType::DIVISION;
          value.operation.priority = 1;
          break;
        case '%':
          value.operation.type = OperationType::MODULATION;
          value.operation.priority = 1;
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

