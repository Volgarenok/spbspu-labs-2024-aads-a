#ifndef	CALCULATE_POSTFIX_HPP
#define	CALCULATE_POSTFIX_HPP
#include "queue.hpp"
#include "stack.hpp"
#include <string>

namespace chernov
{
  using queue = Queue< std::string >;
  using stack = Stack< long long int >;
  void convertToValues(Queue< queue >& postfix_queue, stack& result_stack);
}

#endif
