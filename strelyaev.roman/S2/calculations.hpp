#ifndef CALCULATIONS
#define CALCULATIONS
#include <string>
#include <iosfwd>
#include "stack.hpp"
namespace strelyaev
{
  bool isOperation(std::string& c);
  bool isBracket(std::string& c);
  int getPrecedence(char);
  long long calculateOperation(long long, long long, char);
}
#endif
