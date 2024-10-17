#ifndef EVALUATE_POSTFIX_EXPRESSION_HPP
#define EVALUATE_POSTFIX_EXPRESSION_HPP

#include <iostream>

namespace belokurskaya
{
  int mod(long long int a, long long int b);
  bool isOperator(char c);
  void safeStrCopy(char* dest, const char* src, size_t max_len);
  bool safeAdd(long long int a, long long int b, long long int& result);
  bool willMultiplyOverflowOrUnderflow(long long int a, long long int b, char* errorType);
  bool willSubtractUnderflow(long long int a, long long int b);

  long long int evaluatePostfixExpression(std::string expression);
}

#endif
