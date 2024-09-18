#ifndef GENERATE_HPP
#define GENERATE_HPP
#include <random>

namespace baranov
{
  template < typename T >
  T getRandomNumber(std::default_random_engine & generator, const T &)
  {
    std::uniform_int_distribution< T > dis(std::numeric_limits< T >::min(), std::numeric_limits< T >::max());
    return dis(generator);
  }
  float getRandomNumber(std::default_random_engine & generator, const float);
}

#endif

