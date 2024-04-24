#ifndef CHECKS_HPP
#define CHECKS_HPP

#include <string>

namespace ishmuratov
{
  bool isOperator(const std::string& opr);
  bool high_priority(const std::string& opr);
  bool low_priority(const std::string& opr);
}

#endif
