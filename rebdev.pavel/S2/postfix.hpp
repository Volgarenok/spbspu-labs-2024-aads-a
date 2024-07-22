#ifndef POSTFIX_HPP
#define POSTFIX_HPP

#include <string>
#include <queue>

#include "token.hpp"

namespace rebdev
{
  using postFixQueue = std::queue< token >;

  void makePostFix(std::string & str, postFixQueue & queue);
  long long postFixToResult(postFixQueue & queue);
}

#endif
