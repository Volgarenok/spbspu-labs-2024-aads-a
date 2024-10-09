#ifndef	OPERATIONS_HPP
#define	OPERATIONS_HPP
#include <string>

namespace chernov
{
  bool isOperation(const std::string& elem);
  bool priority(const std::string& a, const std::string& b);
}

#endif
