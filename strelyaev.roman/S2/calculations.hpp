#ifndef CALCULATIONS_HPP
#define CALCULATIONS_HPP
#include <string>
#include <iosfwd>
#include "token.hpp"
#include "stack.hpp"
namespace strelyaev
{
  bool isOperation(const std::string& c);
  bool isBracket(const std::string& c);
  int getPrecedence(char);
  long long calculateOperation(const ExpressionUnit&, const ExpressionUnit&, const ExpressionUnit&);
  bool isPrecedenceLess(char, char);
}
#endif


