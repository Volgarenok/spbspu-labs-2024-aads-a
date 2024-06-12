#ifndef DETECT_SYM_HPP
#define DETECT_SYM_HPP
#include <string>

namespace spiridonov
{
  bool isNumber(const std::string& s);
  bool isOp(const std::string& s);
  bool isLeftBracket(const std::string& s);
  bool isRightBracket(const std::string& s);
  size_t evalPriority(char op);
  bool priorityEqualOrGreater(char op1, char op2);
  int opPlus(int a, int b);
  int opMinus(int a, int b);
  int opMultiply(int a, int b);
  int opDiv(int a, int b);
  int opMod(int a, int b);
}

#endif
