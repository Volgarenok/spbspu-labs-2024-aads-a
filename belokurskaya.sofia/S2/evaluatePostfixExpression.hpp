#ifndef EVALUATE_POSTFIX_EXPRESSION_HPP
#define EVALUATE_POSTFIX_EXPRESSION_HPP

#include <iostream>

namespace belokurskaya
{
  bool isOperator(char c);

  int evaluatePostfixExpression(std::string expression);
}

#endif
