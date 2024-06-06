#ifndef GENERATE_NUMBERS_HPP
#define GENERATE_NUMBERS_HPP

#include <vector>
#include <cstddef>
#include <random>

namespace namestnikov
{
  template< class T >
  T generateNumber(T minNumber, T maxNumber)
  {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution< float > dist(minNumber, maxNumber);
    return static_cast< T >(dist(gen));
  }
}

#endif
