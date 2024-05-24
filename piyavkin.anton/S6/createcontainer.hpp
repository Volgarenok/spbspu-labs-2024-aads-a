#ifndef CREATECONTAINER_HPP
#define CREATECONTAINER_HPP
#include <deque>
#include <random>
#include <limits>
#include <forward_list>
#include <list.hpp>

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
    static float get_value(std::default_random_engine& gen, float);
  }
  template< class T >
  void create_containers(std::deque< T >& deque, List< T >& bi_list, std::forward_list< T >& list,
    size_t n, std::default_random_engine& gen)
  {
    for (size_t i = 0; i < n; ++i)
    {
      T value = detail::get_value(gen, T());
      deque.push_front(value);
      bi_list.push_front(value);
      list.push_front(value);
    }
  }
}
#endif
