#include "manageData.h"

namespace stepanov
{
  void manageExpression::parseExpression(const std::string& input)
  {
    std::string token;
    std::string number;
    for (size_t i = 0; i < input.length(); i++)
    {
      token = input[i];
      Token pushToken(const_cast<char*>(token.c_str()));
      if (i == input.length() - 1)
      {
        if (!number.empty() && pushToken.getTokenType() == OPERAND)
        {
          number += input[i];
          Token pushNumber(const_cast<char*>(number.c_str()));
          newExpr_.pushFront(pushNumber);
        }
        else if (pushToken.getTokenType() == OPERAND)
        {
          newExpr_.pushFront(pushToken);
        }
        break;
      }
      if (token == " ")
      {
        if (!number.empty())
        {
          Token pushNumber(const_cast<char*>(number.c_str()));
          newExpr_.pushFront(pushNumber);
          number = "";
        }
        continue;
      }
      if (pushToken.getTokenType() == OPERAND)
      {
        number += token;
        continue;
      }
      newExpr_.pushFront(pushToken);
    }
  }

  int manageExpression::checkOperatorsPriority(Token token) const
  {
    while (true)
    {
      switch (token.getOperator())
      {
        case '%' :
          return 1;
        case '/':
          return 1;
        case '*':
          return 1;
        case '+':
          return 2;
        case '-':
          return 2;
      }
      return 0;
    }
  }

}
