#ifndef GENERATE_HPP
#define GENERATE_HPP
#include <random>

namespace strelyaev
{
  namespace detail
  {
    template< class T >
    T randomNumber(std::default_random_engine& generator, const T&)
    {
      std::uniform_int_distribution< T > dis(std::numeric_limits< T >::min(), std::numeric_limits< T >::max());
      return dis(generator);
    }
    float randomNumber(std::default_random_engine& generate, float);
  }
}


#endif
