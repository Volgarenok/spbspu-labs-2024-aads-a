#ifndef SORT_AND_PRINT_SEQUENCE
#define SORT_AND_PRINT_SEQUENCE

#include <ostream>
#include <list>
#include <deque>
#include <algorithm>
#include <iomanip>
#include <forward_list>
#include "sortings.hpp"

namespace novokhatskiy
{
  template< class T >
  T getRandomValue()
  {
    return static_cast< T >(std::rand());
  }

  template< class It >
  void printSeq(It begin, It end, std::ostream& out)
  {
    if (begin != end)
    {
      out << *begin;
      while (++begin != end)
      {
        out << ' ' << *begin;
      }
    }
  }

  template< class It, class Cmp >
  void optSort(It begin, It end, std::ostream& out, Cmp cmp, void(*sort)(It, It, Cmp))
  {
    sort(begin, end, cmp);
    printSeq(begin, end, out);
    out << '\n';
  }

  template< class T, class Cmp >
  void sortSeq(size_t size, std::ostream& out)
  {
    using namespace novokhatskiy;
    std::deque< T > deque(size);
    std::generate(deque.begin(), deque.end(), getRandomValue< T >);
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
  }
}

#endif
