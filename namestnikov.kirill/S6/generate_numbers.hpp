#ifndef GENERATE_NUMBERS_HPP
#define GENERATE_NUMBERS_HPP

#include <vector>

template< class T >
T generateNumber(T minNumber, T maxNumber)
{
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution< float > dist(minNumber, maxNumber);
  return static_cast< T >(dist(gen));
}

namespace namestnikov
{
  template< class T >
  std::vector< T > generateNumbers(size_t size)
  {
    std::vector< T > data(size);
    for (size_t i = 0; i < size; ++i)
    {
      data[i] = generateNumber< T >(-1000, 1000);
    }
    return data;
  }
}

#endif