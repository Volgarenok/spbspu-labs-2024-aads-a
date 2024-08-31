#ifndef SORTINGS_HPP
#define SORTINGS_HPP

#include <deque>
#include <ctime>

namespace belokurskaya
{
  template < typename T >
  T generateRandomNumbers(size_t size)
  {
    return static_cast< T >(std::rand());
  }
}

#endif

