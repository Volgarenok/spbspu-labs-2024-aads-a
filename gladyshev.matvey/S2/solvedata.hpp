#ifndef SOLVEDATA_HPP
#define SOLVEDATA_HPP

#include <istream>

#include "stack.hpp"
#include "queue.hpp"

namespace gladyshev
{
  long long int gladyshev::evaluatePostfix(Queue< std::string >& postfix);
  void inputExpression(std::istream& in, Stack< long long int >& results);
}

#endif
