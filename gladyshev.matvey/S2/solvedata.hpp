#ifndef SOLVEDATA_HPP
#define SOLVEDATA_HPP

#include <istream>

#include <queue.hpp>

#include "stack.hpp"

namespace gladyshev
{
  long long int evaluatePostfix(Queue< std::string >& postfix);
  void inputExpression(std::istream& in, Stack< long long int >& results);
}

#endif
