#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include <deque>
#include <ctime>

namespace belokurskaya
{
  template < typename T >
  T generateRandomNumbers()
  {
    return static_cast< T >(std::rand());
  }
}

#endif
