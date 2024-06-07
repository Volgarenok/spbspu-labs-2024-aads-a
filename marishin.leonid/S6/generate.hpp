#ifndef GENERATE_HPP
#define GENERATE_HPP
#include <random>

namespace marishin
{
  namespace detail
  {
    template< class T >
    T randomNumber(std::default_random_engine& generator)
    {
      std::uniform_real_distribution< float > dist(-1000, 1000);
      return static_cast< T >(dist(generator));
    }
  }
}


#endif
