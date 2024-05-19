#ifndef CREATECONTAINER_HPP
#define CREATECONTAINER_HPP
#include <deque>
#include <random>
#include <forward_list>
#include <list.hpp>

namespace piyavkin
{
  namespace detail
  {
    int get_value(int);
    float get_value(float);
  }
  template< class T >
  void create_containers(std::deque< T >& deque, List< T >& bi_list, std::forward_list< T >& list, size_t n)
  {
    for (size_t i = 0; i < n; ++i)
    {
      T value = detail::get_value(T());
      deque.push_front(value);
      bi_list.push_front(value);
      list.push_front(value);
    }
  }
}
#endif
