#ifndef INFIX_OPERATIONS_HPP
#define INFIX_OPERATIONS_HPP

#include <string>
#include "queue.hpp"

namespace ishmuratov
{
  void input_infix(const std::string & line, Queue< std::string > & input_queue);
  void topostfix(Queue< std::string > & process_queue, Queue< std::string > & result_queue);
}

#endif
