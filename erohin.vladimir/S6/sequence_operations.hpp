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
    return (std::rand() % (max - min) + min);
  }

  template<>
  float getRandom< float >(float min, float max)
  {
    return ((static_cast< float >(std::rand()) / RAND_MAX) * (max - min) + min);
  }

  template< class T, class Container >
  void generateRandomSequence(Container & cnt, size_t n)
  {
    List< T > seq;
    for (size_t i = 0; i < n; ++i)
    {
      seq.push_front(getRandom< T >(-1000, 1000));
    }
    Container temp(seq.begin(), seq.end());
    cnt.clear();
    cnt = std::move(temp);
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
