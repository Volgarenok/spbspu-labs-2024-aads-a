#ifndef PRINTSORTCONTAINERS_HPP
#define PRINTSORTCONTAINERS_HPP
#include <ostream>
#include <deque>
#include <forward_list>
#include <list.hpp>

namespace piyavkin
{
  template< class T >
  void print_containers(std::ostream& out, const T& container)
  {
    for (auto i = container.begin(); i != container.end(); ++i)
    {
      if (i != container.begin())
      {
        out << ' ';
      }
      out << *i;
    }
    out << '\n';
  }
  template< class T >
  void print_sort_containers(std::ostream& out, std::deque< T >& deque, List< T >& bi_list, std::forward_list< T >& list)
  {

  }
}
#endif