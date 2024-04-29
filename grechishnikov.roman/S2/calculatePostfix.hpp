#ifndef CALCULATE_POSTFIX_HPP
#define CALCULATE_POSTFIX_HPP

#include <cstddef>
#include <string>
#include "queue.hpp"

namespace grechishnikov
{
  long long int calculatePostfix(const Queue< std::string >& postfix);
}

#endif
