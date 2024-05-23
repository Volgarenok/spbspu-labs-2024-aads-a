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
  void printer(std::ostream& out, const Container& container)
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
  comparator cmp{};
  generator< value_type > gen(0, 1000);
  std::deque< value_type > deque_sort;
  std::generate_n(std::back_inserter(deque_sort), size, gen);
  printer(out, deque_sort);

  std::deque< value_type > deque_shell(deque_sort.cbegin(), deque_sort.cend());
  //  deque< value_type > deque_bucket(deque_inbuild.cbegin(),deque_inbuild.cend());;

  ForwardList< value_type > forward_sort(deque_sort.cbegin(), deque_sort.cend());
  ForwardList< value_type > forward_shell(deque_sort.cbegin(), deque_sort.cend());
  std::list< value_type > list_shell(deque_sort.cbegin(), deque_sort.cend());

  std::sort(deque_sort.begin(), deque_sort.end(), cmp);
  forward_sort.sort(cmp);
  shellSort(deque_shell.begin(), deque_shell.end(), cmp);
  shellSort(forward_shell.begin(), forward_shell.end(), cmp);
  shellSort(list_shell.begin(), list_shell.end(), cmp);
  //  bucketSort(deque_sort.begin(), deque_sort.end(), cmp);

  printer(out, deque_sort);
  printer(out, deque_shell);
  //  printer(out, deque_bucket);
  printer(out, forward_sort);
  printer(out, forward_shell);
  printer(out, list_shell);
  printer(out, list_shell); //for del
}
#endif
