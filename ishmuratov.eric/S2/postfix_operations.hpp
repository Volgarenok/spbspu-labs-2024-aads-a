#ifndef POSTFIX_OPERATIONS_HPP
#define POSTFIX_OPERATIONS_HPP

#include <string>
#include "queue.hpp"
#include "stack.hpp"

namespace ishmuratov
{
  void calculate_postfix(Queue< std::string > & result_queue, Stack< long long int > & operands);
}

#endif
