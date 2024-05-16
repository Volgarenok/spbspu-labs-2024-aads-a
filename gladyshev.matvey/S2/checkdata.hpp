#ifndef CHECKDATA_HPP
#define CHECKDATA_HPP

#include <string>

namespace gladyshev
{
  bool isOperator(const std::string& op);
  bool checkQuality(const std::string& top, const std::string& now);
}

#endif
