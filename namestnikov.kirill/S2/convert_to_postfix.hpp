#ifndef CONVERT_TO_POSTFIX_HPP
#define CONVERT_TO_POSTFIX_HPP

#include <queue>
#include <string>
#include "queue.hpp"

namespace namestnikov
{
  void convertToPostfix(Queue< std::string > & currentQueue, Queue< std::string > & resultQueue);
}

#endif
