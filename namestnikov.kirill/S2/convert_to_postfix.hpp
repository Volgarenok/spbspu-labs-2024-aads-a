#ifndef CONVERT_TO_POSTFIX_HPP
#define CONVERT_TO_POSTFIX_HPP

#include <queue>
#include <string>
#include "queue.hpp"
#include "data_types.hpp"

namespace namestnikov
{
  void convertToPostfix(Queue< namestnikov::Key > & currentQueue, Queue< namestnikov::Key > & resultQueue);
}

#endif
