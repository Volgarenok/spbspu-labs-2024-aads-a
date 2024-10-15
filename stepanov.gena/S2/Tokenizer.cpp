#include "Tokenizer.h"

namespace stepanov
{
  Token::Token(char* token):
    token_(token),
    type_(NONE),
    numData_(0),
    charData_('a')
  {}

  bool Token::isOperand() const noexcept
  {
    if (type_ != NONE)
    {
      return (type_ == OPERAND);
    }
    size_t length = strlen(token_);
    for (size_t i = 0; i < length; i++)
    {
      if (!isdigit(token_[i]))
      {
        return false;
      }
    }
    return true;
  }

  bool Token::isOperator() noexcept
  {
    if (*token_ == '+' || *token_ == '-' || *token_ == '*' || *token_ == '%' || *token_ == '/')
    {
      return true;
    }
    return false;
  }

  bool Token::isParenthesis() const noexcept
  {
    if (type_ != NONE)
    {
      return (type_ == LEFT_PAREN || type_ == RIGHT_PAREN);
    }
    if (*token_ == '(' || *token_ == ')')
    {
      return true;
    }
    return false;
  }

  TokenType Token::getOperatorType() noexcept
  {
    switch (*token_)
    {
      case '+':
        return PLUS;
      case '-':
        return MINUS;
      case '*':
        return MULTIPLICATION;
      case '/':
        return DIV;
      case '%':
        return MOD;
      default :
        break;
    }
    return NONE;
  }

  TokenType Token::getTokenType() const noexcept
  {
    return type_;
  }
  char Token::getParenthesis() const noexcept
  {
    return charData_;
  }
  char Token::getOperator() noexcept
  {
    return charData_;
  }
  long long Token::getOperand() const noexcept
  {
    return numData_;
  }
}
