#ifndef EXECUTOR_HPP
#define EXECUTOR_HPP
#include <ostream>
#include <deque>
#include <list>
#include <algorithm>
#include <random>
#include <forward_list.hpp>
#include "generators.hpp"
#include "sorting_algorithms.hpp"

namespace detail
{
  template< typename Container, typename value_type = typename Container::const_iterator::value_type >
  void print(std::ostream& out, const Container& container)
  {
    typename Container::const_iterator it = container.cbegin();
    out << *it;
    for (++it; it != container.cend(); ++it)
    {
      out << ' ' << *it;
    }
    out << '\n';
  }
}

template< typename value_type, typename comparator >
void sortirator(std::ostream& out, size_t size)
{
  using namespace zaitsev;
  using namespace detail;
  generator< value_type > gen(0, 1000);
  std::deque< value_type > deque_sort;
  std::generate_n(std::back_inserter(deque_sort), size, gen);
  print(out, deque_sort);

  std::deque< value_type > deque_shell(deque_sort.cbegin(), deque_sort.cend());
  std::deque< value_type > deque_bucket(deque_inbuild.cbegin(),deque_inbuild.cend());;

  ForwardList< value_type > forward_sort(deque_sort.cbegin(), deque_sort.cend());
  ForwardList< value_type > forward_shell(deque_sort.cbegin(), deque_sort.cend());
  std::list< value_type > list_shell(deque_sort.cbegin(), deque_sort.cend());

  std::sort(deque_sort.begin(), deque_sort.end(), comparator{});
  forward_sort.sort(comparator{});
  shellSort(deque_shell.begin(), deque_shell.end(), comparator{});
  shellSort(forward_shell.begin(), forward_shell.end(), comparator{});
  shellSort(list_shell.begin(), list_shell.end(), comparator{});
  bucketSort(deque_sort.begin(), deque_sort.end(), comparator{});

  print(out, deque_sort);
  print(out, deque_shell);
  printer(out, deque_bucket);
  print(out, forward_sort);
  print(out, forward_shell);
  print(out, list_shell);
}
#endif
