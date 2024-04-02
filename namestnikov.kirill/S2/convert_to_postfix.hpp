#ifndef CONVERT_TO_POSTFIX_HPP
#define CONVERT_TO_POSTFIX_HPP

#include <queue>
#include <string>

namespace namestnikov
{
  void convertToPostfix(std::queue< std::string > & currentQueue, std::queue< std::string > & resultQueue);
}

#endif