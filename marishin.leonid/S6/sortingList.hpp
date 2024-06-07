#ifndef SORTINGSHEETS_HPP
#define SORTINGSHEETS_HPP
#include <algorithm>
#include <cstdlib>
#include <deque>
#include <forward_list>
#include <iostream>
#include <linkedList.hpp>
#include <list>
#include <string>
#include "print.hpp"
#include "sorting.hpp"

namespace marishin
{
  template< class T >
  T randomNumber()
  {
    return static_cast< T >(std::rand());
  }

  template < class It, class Cmp >
  void chooseSort(std::ostream& out, It begin, It end, Cmp cmp, void (*sort)(It, It, Cmp))
  {
    sort(begin, end, cmp);
    print(out, begin, end);
    out << '\n';
  }

  template < class LinkedList, class Cmp >
  void standartSort(std::ostream& out, LinkedList& list, Cmp cmp)
  {
    list.sort(cmp);
    print(out, list.begin(), list.end());
    out << '\n';
  }

  template < class Type, class Cmp >
  void sortAndPrint(size_t size, std::ostream& out)
  {
    std::deque< Type > deque(size);
    std::generate(deque.begin(), deque.end(), randomNumber< Type >);
    LinkedList< Type > bi_list(deque.cbegin(), deque.cend());
    std::list< Type > bi_list_standart(deque.cbegin(), deque.cend());
    std::deque< Type > deque_sort(deque.cbegin(), deque.cend());
    std::deque< Type > deque_qsort(deque.cbegin(), deque.cend());
    std::deque< Type > deque_shaker(deque.cbegin(), deque.cend());
    std::forward_list< Type > forward_list(deque.cbegin(), deque.cend());
    print(out, forward_list.begin(), forward_list.end());
    out << "\n";
    Cmp cmp;
    chooseSort(out, bi_list.begin(), bi_list.end(), cmp, QSort);
    chooseSort(out, deque_qsort.begin(), deque_qsort.end(), cmp, QSort);
    chooseSort(out, deque_shaker.begin(), deque_shaker.end(), cmp, shaker);
    standartSort(out, bi_list_standart, cmp);
    standartSort(out, forward_list, cmp);

    std::sort(deque_sort.begin(), deque_sort.end(), cmp);
    print(out, deque_sort.begin(), deque_sort.end());
    out << "\n";
  }
}
#endif
