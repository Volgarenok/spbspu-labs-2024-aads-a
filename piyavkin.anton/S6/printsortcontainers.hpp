#ifndef PRINTSORTCONTAINERS_HPP
#define PRINTSORTCONTAINERS_HPP
#include <ostream>
#include <deque>
#include <forward_list>
#include <algorithm>
#include <iomanip>
#include "timsort.hpp"
#include "streamguard.hpp"

namespace piyavkin
{
  template< class T >
  void print_container(std::ostream& out, const T& container)
  {
    StreamGuard guard(out);
    out << std::fixed << std::setprecision(1);
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
  void print_sorted_containers(std::ostream& out, std::deque< T >& deque, List< T >& bi_list, std::forward_list< T >& list, Cmp cmp)
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
    print_container(out, deq_mer);
    print_container(out, deq_tim);
    print_container(out, deque);
    print_container(out, list);
    print_container(out, bi_list);
    print_container(out, bi_list_mer);
  }
}
#endif
