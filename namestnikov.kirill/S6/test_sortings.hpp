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
    std::forward_list< T > forwardlistSelection(data.begin(), data.end());
    std::list< T > listSelection(data.begin(), data.end());
    std::list< T > listShell(data.begin(), data.end());
    std::deque< T > dequeSelection(data.begin(), data.end());
    std::deque< T > dequeShell(data.begin(), data.end());
    doSelectionSort(forwardlistSelection.begin(), size, compare);
    doSelectionSort(listSelection.begin(), size, compare);
    doShellSort(listShell.begin(), size, compare);
    doSelectionSort(dequeSelection.begin(), size, compare);
    doShellSort(dequeShell.begin(), size, compare);
    printData(forwardlistSelection.begin(), forwardlistSelection.end(), out);
    printData(listSelection.begin(), listSelection.end(), out);
    printData(listShell.begin(), listShell.end(), out);
    printData(dequeSelection.begin(), dequeSelection.end(), out);
    printData(dequeShell.begin(), dequeShell.end(), out);
  }
}

#endif