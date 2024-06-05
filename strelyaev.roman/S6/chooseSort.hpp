#ifndef CHOOSESORT_HPP
#define CHOOSESORT_HPP
#include <algorithm>
#include <cstdlib>
#include <deque>
#include <forward_list>
#include <iostream>
#include <list>
#include <string>
#include "../common/list/list.hpp"
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
    List< Type > biListR(array, array + size);
    std::list< Type > biListSt(array, array + size);
    std::deque< Type > dequeSort(array, array + size);
    std::deque< Type > dequeBubble(array, array + size);
    std::deque< Type > dequeShell(array, array + size);
    std::forward_list< Type > forwardList(array, array + size);
    print(out, forwardList.begin(), forwardList.end());
    out << "\n";

    chooseSort(out, biListR.begin(), biListR.end(), cmp, bubble_sort);
    chooseSort(out, dequeBubble.begin(), dequeBubble.end(), cmp, bubble_sort);
    chooseSort(out, dequeShell.begin(), dequeShell.end(), cmp, shell_sort);
    standartSort(out, biListSt, cmp);
    standartSort(out, forwardList, cmp);

    std::sort(dequeSort.begin(), dequeSort.end(), cmp);
    print(out, dequeSort.begin(), dequeSort.end());
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