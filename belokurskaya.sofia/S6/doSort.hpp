#ifndef DOSORT_HPP
#define DOSORT_HPP

#include <iostream>
#include <list>
#include <forward_list>
#include <deque>
#include <algorithm>

#include "list.hpp"
#include "generator.hpp"
#include "sortings.hpp"

namespace belokurskaya
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

  template < class Type, class Cmp >
  void sortAndPrint(size_t size, std::ostream& out)
  {
    std::deque< Type > deque(size);
    std::generate(deque.begin(), deque.end(), generateRandomNumbers< Type >);

    std::list< Type > list(deque.cbegin(), deque.cend());

    std::deque< Type > deque_sort(deque.cbegin(), deque.cend());
    std::deque< Type > deque_shaker(deque.cbegin(), deque.cend());
    std::deque< Type > deque_quicksort(deque.cbegin(), deque.cend());

    List< Type > forward_list(deque.cbegin(), deque.cend());
    std::forward_list< Type > forward_list_standart(deque.cbegin(), deque.cend());

    print(out, forward_list.begin(), forward_list.end());
    out << "\n";

    Cmp cmp;
    chooseSort(out, list.begin(), list.end(), cmp, quickSort);
    chooseSort(out, deque_shaker.begin(), deque_shaker.end(), cmp, shakerSort);
    chooseSort(out, deque_quicksort.begin(), deque_quicksort.end(), cmp, quickSort);

    standartSort(out, list, cmp);
    standartSort(out, forward_list_standart, cmp);

    std::sort(deque_sort.begin(), deque_sort.end(), cmp);
    print(out, deque_sort.begin(), deque_sort.end());
    out << "\n";
  }
}

#endif
