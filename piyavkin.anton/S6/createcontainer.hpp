#ifndef CREATECONTAINER_HPP
#define CREATECONTAINER_HPP
#include <random>
#include <limits>
#include <forward_list>
#include <list.hpp>
#include <deque>

namespace piyavkin
{
  namespace detail
  {
    template< class T >
    T get_value(std::default_random_engine& gen, const T&)
    {
      std::uniform_int_distribution< T > dis(std::numeric_limits< T >::min(), std::numeric_limits< T >::max());
      return dis(gen);
    }
    float get_value(std::default_random_engine& gen, float);
  }
}
#endif
