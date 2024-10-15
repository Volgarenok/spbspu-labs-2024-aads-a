#ifndef TOKEN_TYPE_HPP
#define TOKEN_TYPE_HPP
#include <string>

namespace sakovskaia
{
  bool isOperator(const std::string & token);
  bool isOperand(const std::string & token);
}

#endif
