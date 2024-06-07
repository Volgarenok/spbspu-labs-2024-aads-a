#ifndef SEQUENCE_OPERATIONS_HPP
#define SEQUENCE_OPERATIONS_HPP

#include <iterator>
#include <iostream>
#include "list.hpp"

namespace erohin
{
  template< class T >
  T getRandom(T min, T max)
  {
    return ((static_cast< float >(std::rand()) / RAND_MAX) * (max - min) + min);
  }

  template< class OutputIt >
  void printSequence(std::ostream & output, OutputIt begin, OutputIt end)
  {
    if (begin == end)
    {
      return;
    }
    output << *(begin++);
    while (begin != end)
    {
      output << " " << *(begin++);
    }
  }
}

#endif
