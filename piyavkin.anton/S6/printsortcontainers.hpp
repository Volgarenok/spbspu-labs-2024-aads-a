#ifndef PRINTSORTCONTAINERS_HPP
#define PRINTSORTCONTAINERS_HPP
#include <ostream>
#include <deque>
#include <forward_list>
#include <algorithm>
#include <list.hpp>
#include "timsort.hpp"

namespace piyavkin
{
  template< class T >
  void print_containers(std::ostream& out, const T& container)
  {
    for (auto i = container.cbegin(); i != container.cend(); ++i)
    {
      if (i != container.cbegin())
      {
        out << ' ';
      }
      out << *i;
    }
    out << '\n';
  }
  template< class T, class Cmp >
  void print_sort_containers(std::ostream& out, std::deque< T >& deque, List< T >& bi_list, std::forward_list< T >& list, Cmp cmp)
  {
    std::deque< T > deq_tim = deque;
    std::deque< T > deq_mer = deque;
    List< T > bi_list_mer = bi_list;
    sort_merge(deq_mer.begin(), deq_mer.end(), cmp);
    sort_merge(bi_list_mer.begin(), bi_list_mer.end(), cmp);
    timsort(deq_tim.begin(), deq_tim.size(), cmp);
    bi_list.sort(cmp);
    list.sort(cmp);
    std::sort(deque.begin(), deque.end(), cmp);
    print_containers(out, deq_mer);
    print_containers(out, deq_tim);
    print_containers(out, deque);
    print_containers(out, list);
    print_containers(out, bi_list);
    print_containers(out, bi_list_mer);
  }
}
#endif