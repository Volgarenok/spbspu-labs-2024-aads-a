#ifndef PROCESS_EXPRESSIONS_HPP
#define PROCESS_EXPRESSIONS_HPP

#include <iostream>
#include "evaluatePostfix.hpp"

namespace skuratov
{
  void printReverse(const Queue< long long int >& queue);
  void processExpressions(const List< std::string >& exp);
}

#endif
