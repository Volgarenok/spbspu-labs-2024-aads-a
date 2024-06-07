#ifndef TOKEN_TYPE_HPP
#define TOKEN_TYPE_HPP

#include <string>

namespace grechishnikov
{
  bool isOperator(const std::string& token);
  bool isOperand(const std::string& token);
}

#endif
