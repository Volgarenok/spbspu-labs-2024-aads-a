#ifndef SORT_AND_PRINT_SEQUENCE
#define SORT_AND_PRINT_SEQUENCE

#include <algorithm>
#include <deque>
#include <forward_list>
#include <iomanip>
#include <list>
#include <ostream>
#include <stdexcept>
#include "sortings.hpp"

namespace novokhatskiy
{
  template < class It >
  void printSeq(It begin, It end, std::ostream& out)
  {
    if (begin != end)
    {
      out << *begin;
      while (++begin != end)
      {
        out << ' ' << *begin;
      }
      out << '\n';
    }
  }

  template < class It, class Cmp >
  void optSort(It begin, It end, std::ostream& out, Cmp cmp, void (*sort)(It, It, Cmp))
  {
    sort(begin, end, cmp);
    printSeq(begin, end, out);
  }

  template < class T, class Cmp >
  void sortSeq(size_t size, std::ostream& out)
  {
    using namespace novokhatskiy;
    std::deque< T > deque;
    T value;
    for (size_t i = 0; i != size; i++)
    {
      value = static_cast< T >(std::rand() / (static_cast< T >(RAND_MAX / RAND_MAX)));
      deque.push_back(value);
    }
    std::forward_list< T > forwardList(deque.cbegin(), deque.cend());
    std::list< T > biList(deque.cbegin(), deque.cend());
    std::list< T > secondBiList(deque.cbegin(), deque.cend());
    std::deque< T > secondDeque(deque.cbegin(), deque.cend());
    std::deque< T > thirdDeque(deque.cbegin(), deque.cend());
    out << std::setprecision(1) << std::fixed;
    Cmp cmp;
    optSort(forwardList.begin(), forwardList.end(), out, cmp, doInsertionSort);
    optSort(biList.begin(), biList.end(), out, cmp, doInsertionSort);
    optSort(secondBiList.begin(), secondBiList.end(), out, cmp, doShakerSort);
    optSort(deque.begin(), deque.end(), out, cmp, doInsertionSort);
    optSort(secondDeque.begin(), secondDeque.end(), out, cmp, doShakerSort);
    optSort(thirdDeque.begin(), thirdDeque.end(), out, cmp, doInsertionSort);
    out << '\n';
  }
}

#endif
