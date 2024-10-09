#ifndef	INFIX_TO_POSTFIX_HPP
#define	INFIX_TO_POSTFIX_HPP
#include "queue.hpp"
#include <iostream>
#include <string>

namespace chernov
{
  using queue = Queue< std::string >;
  void inputInfix(std::istream& in, Queue< queue >& infix_queue);
  void convertToPostfix(Queue< queue >& infix_queue, Queue< queue >& postfix_queue);
}

#endif
