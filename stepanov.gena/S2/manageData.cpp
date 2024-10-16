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

  void manageExpression::convertToPolish(const std::string& newString)
  {
    parseExpression(newString);
    while (!newExpr_.isEmpty())
    {
      if (newExpr_.getSize() == 1 && !newExpr_.getTail().isOperand())
      {
        throw std::runtime_error("Incorrect expression!");
      }
      if (newExpr_.getTail().isOperand())
      {
        postfQueue_.pushFront(newExpr_.getTail());
      }
      else if (newExpr_.getTail().getParenthesis() == '(')
      {
        stack_.pushTop(newExpr_.getTail());
      }
      else if (checkOperatorsPriority(newExpr_.getTail()) != 0)
      {
        while (!stack_.isEmpty() && (checkOperatorsPriority(newExpr_.getTail()) <= checkOperatorsPriority(stack_.getHead())))
        {
          postfQueue_.pushFront(stack_.getHead());
          stack_.popTop();
        }
        stack_.pushTop(newExpr_.getTail());
      }
      else if (newExpr_.getTail().getParenthesis() == ')')
      {
        while (stack_.getHead().getParenthesis() != '(')
        {
          postfQueue_.pushFront(stack_.getHead());
          stack_.popTop();
        }
        if (stack_.getHead().getParenthesis() == '(')
        {
          stack_.popTop();
        }
      }
      newExpr_.popBack();
    }
    while (!stack_.isEmpty())
    {
      if (stack_.getHead().isParenthesis())
      {
        stack_.popTop();
      }
      else
      {
        postfQueue_.pushFront(stack_.getHead());
        stack_.popTop();
      }
    }
  }
}



