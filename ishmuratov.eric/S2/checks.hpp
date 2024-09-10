#ifndef CHECKS_HPP
#define CHECKS_HPP

#include <string>

namespace ishmuratov
{
  bool is_operator(const std::string & opr);
  int get_priority(const std::string & opr);
}

#endif
