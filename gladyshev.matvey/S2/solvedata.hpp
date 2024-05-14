#ifndef SOLVEDATA_HPP
#define SOLVEDATA_HPP

#include <istream>

#include "stack.hpp"

namespace gladyshev
{
  void inputExpression(std::istream& in, Stack< long long int >& results);
}

#endif
