#ifndef CHOOSESORT_HPP
#define CHOOSESORT_HPP
#include <algorithm>
#include <cstdlib>
#include <deque>
#include <forward_list>
#include <iostream>
#include <list>
#include <string>
#include <list/list.hpp>
#include "generate.hpp"
#include "print.hpp"
#include "sorts.hpp"

namespace strelyaev
{
  template < class It, class Cmp >
  void chooseSort(std::ostream& out, It begin, It end, Cmp cmp, void (*sort)(It, It, Cmp))
  {
    sort(begin, end, cmp);
    print(out, begin, end);
    out << '\n';
  }

  template < class List, class Cmp >
  void standartSort(std::ostream& out, List& list, Cmp cmp)
  {
    list.sort(cmp);
    print(out, list.begin(), list.end());
    out << '\n';
  }

  template < class Type, class Compare >
  void sortAndPrint(std::ostream& out, size_t size, Type array[], Compare cmp)
  {
    List< Type > bi_list(array, array + size);
    std::list< Type > bi_list_standart(array, array + size);
    std::deque< Type > deque_sort(array, array + size);
    std::deque< Type > deque_bubble(array, array + size);
    std::deque< Type > deque_shell(array, array + size);
    std::forward_list< Type > forward_list(array, array + size);
    print(out, forward_list.begin(), forward_list.end());
    out << "\n";

    chooseSort(out, bi_list.begin(), bi_list.end(), cmp, bubble_sort);
    chooseSort(out, deque_bubble.begin(), deque_bubble.end(), cmp, bubble_sort);
    chooseSort(out, deque_shell.begin(), deque_shell.end(), cmp, shell_sort);
    standartSort(out, bi_list_standart, cmp);
    standartSort(out, forward_list, cmp);

    std::sort(deque_sort.begin(), deque_sort.end(), cmp);
    print(out, deque_sort.begin(), deque_sort.end());
    out << "\n";
  }

  template < class Type, class Compare >
  void fillContainer(std::ostream& out, size_t size, std::default_random_engine& generate)
  {
    Type array[10000];
    for (size_t i = 0; i < size; ++i)
    {
      array[i] = detail::randomNumber(generate, Type());
    }
    sortAndPrint(out, size, array, Compare());
  }
}

#endif
