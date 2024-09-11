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
  template< class It >
  void print_container(std::ostream& out, It begin, It end)
  {
    StreamGuard guard(out);
    out << std::fixed << std::setprecision(1);
    out << *begin;
    for (auto i = ++begin; i != end; ++i)
    {
      out << ' ' << *i;
    }
  }
  template< class It, class Cmp >
  void choose_sort(std::ostream& out, It begin, It end, Cmp cmp, void (*sort)(It, size_t, Cmp))
  {
    sort(begin, std::distance(begin, end), cmp);
    print_container(out, begin, end);
  }
  template< class Cnt, class Cmp >
  void choose_sort_m(std::ostream& out, Cnt& container, Cmp cmp)
  {
    container.sort(cmp);
    print_container(out, container.cbegin(), container.cend());
  }
  template< class T, class Cmp >
  void print_sorted_containers(std::ostream& out, std::deque< T >& deque, Cmp cmp)
  {
    std::deque< T > deq_tim = deque;
    std::deque< T > deq_mer = deque;
    std::forward_list< T > list(deque.cbegin(), deque.cend());
    List< T > bi_list(deque.cbegin(), deque.cend());
    List< T > bi_list_mer = bi_list;
    choose_sort(out, deq_mer.begin(), deq_mer.end(), cmp, sort_merge);
    out << '\n';
    choose_sort(out, bi_list_mer.begin(), bi_list_mer.end(), cmp, sort_merge);
    out << '\n';
    choose_sort(out, deq_tim.begin(), deq_tim.end(), cmp, timsort);
    out << '\n';
    choose_sort_m(out, bi_list, cmp);
    out << '\n';
    choose_sort_m(out, list, cmp);
    out << '\n';
    std::sort(deque.begin(), deque.end(), cmp);
    print_container(out, deque.cbegin(), deque.cend());
    out << '\n';
  }
}
#endif
