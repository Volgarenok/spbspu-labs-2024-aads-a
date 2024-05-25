#ifndef TEST_SORTINGS_HPP
#define TEST_SORTINGS_HPP

#include <ostream>
#include <cstddef>
#include <vector>
#include <list>
#include <deque>
#include <forward_list>
#include "shell_sort.hpp"
#include "selection_sort.hpp"

template< class Iter >
void printData(Iter first, Iter last, std::ostream & out)
{
  auto temp = first;
  ++temp;
  for (; temp != last; ++temp)
  {
    out << *first << " ";
    ++first;
  }
  out << *first << "\n";
}

namespace namestnikov
{
  template< class T, class Compare >
  void testSortings(std::ostream & out, std::vector< T > data, size_t size, Compare compare)
  {
    printData(data.begin(), data.end(), out);
    std::forward_list myList(data.begin(), data.end());
    printData(myList.begin(), myList.end(), out);
    doSelectionSort(myList.begin(), size, compare);
    printData(myList.begin(), myList.end(), out);
  }
}

#endif