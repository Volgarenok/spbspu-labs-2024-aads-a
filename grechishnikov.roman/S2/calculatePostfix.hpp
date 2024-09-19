#ifndef CALCULATE_POSTFIX_HPP
#define CALCULATE_POSTFIX_HPP

#include <cstddef>
#include <string>
#include <istream>
#include "queue.hpp"
#include "stack.hpp"

namespace grechishnikov
{
  long long int calculatePostfix(const Queue< std::string >& postfix);
  Stack< long long int > calculateExpressions(std::istream& in);
}

#endif
