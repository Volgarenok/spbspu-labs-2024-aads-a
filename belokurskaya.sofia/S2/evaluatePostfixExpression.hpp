#ifndef EVALUATE_POSTFIX_EXPRESSION_HPP
#define EVALUATE_POSTFIX_EXPRESSION_HPP

#include "stack.hpp"

#include <iostream>

bool isOperator(char c)
{
  return c == '+' || c == '-' || c == '*' || c == '/' ||  c == '%';
}

int evaluatePostfixExpression(std::string expression)
{
  Stack< int > st;
  int num = 0;
  int operand1, operand2;
  bool flag = false;

  for (char& c: expression)
  {
    if (isdigit(c))
    {
      num = num * 10 + (c - '0');
      flag = true;
    }
    else if (isspace(c))
    {
      if (flag)
      {
        st.push(num);
        flag = false;
        num = 0;
      }
    }
    else if (isOperator(c))
    {
      operand2 = st.pop();
      operand1 = st.pop();
      if (c == '+')
      {
        st.push(operand1 + operand2);
      }
      else if (c == '-')
      {
        st.push(operand1 - operand2);
      }
      else if (c == '*')
      {
        st.push(operand1 * operand2);
      }
      else if (c == '/')
      {
        st.push(operand1 / operand2);
      }
      else if (c == '%')
      {
        st.push(operand1 % operand2);
      }
    }
    else
    {
      throw std::invalid_argument("Unknown symbol in the argument");
    }
  }
  return st.top();
}

#endif
