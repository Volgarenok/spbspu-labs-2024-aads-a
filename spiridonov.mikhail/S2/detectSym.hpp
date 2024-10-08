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
  int64_t opPlus(int64_t a, int64_t b);
  int64_t opMinus(int64_t a, int64_t b);
  int64_t opMultiply(int64_t a, int64_t b);
  int64_t opDiv(int64_t a, int64_t b);
  int64_t opMod(int64_t a, int64_t b);
}

#endif
