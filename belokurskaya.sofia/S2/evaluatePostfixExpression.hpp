#ifndef EVALUATE_POSTFIX_EXPRESSION_HPP
#define EVALUATE_POSTFIX_EXPRESSION_HPP

#include <iostream>

namespace belokurskaya
{
  bool isOperator(char c);
  void safeStrCopy(char* dest, const char* src, size_t max_len);
  bool safeAdd(long long a, long long b, long long& result);
  bool willMultiplyOverflowOrUnderflow(long long a, long long b, char* errorType);
  bool willSubtractUnderflow(long long a, long long b);

  long long evaluatePostfixExpression(std::string expression);
}

#endif
