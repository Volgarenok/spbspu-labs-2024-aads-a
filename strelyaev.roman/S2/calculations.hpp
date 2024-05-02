#ifndef CALCULATIONS_HPP
#define CALCULATIONS_HPP
#include <string>
#include <iosfwd>
#include "token.hpp"
#include "stack.hpp"
namespace strelyaev
{
  bool isPlusOrMinus(char c);
  bool isMultiplyOrDivision(char c);
  bool isOperation(char c);
  bool isBracket(char c);
  int getPrecedence(char);
  long long calculateOperation(const ExpressionUnit&, const ExpressionUnit&, const ExpressionUnit&);
  bool isPrecedenceLess(char, char);
}
#endif


