#ifndef CONVERT_TO_POSTFIX_HPP
#define CONVERT_TO_POSTFIX_HPP

#include "queue.hpp"
#include "types.hpp"

namespace lopatina
{
  Queue< PostfixType > convertToPostfix(Queue< InfixType > & queue_source);
}

#endif
