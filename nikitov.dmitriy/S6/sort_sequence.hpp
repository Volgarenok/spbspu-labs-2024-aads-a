#ifndef SORT_SEQUENCE_HPP
#define SORT_SEQUENCE_HPP

#include <deque>
#include <forward_list>
#include <algorithm>
#include <iomanip>
#include <list.hpp>
#include <tree.hpp>
#include "sortings.hpp"
#include "iterators_functions.hpp"

namespace nikitov
{
  namespace detail
  {
    int generateValue(int)
    {
      return std::rand();
    }

    float generateValue(float)
    {
      return static_cast <float> (std::rand());
    }
  }

  template< class T, class Compare >
  void sortSequence(size_t size, std::ostream& output)
  {
    std::forward_list< T > fList;
    List< T > firstBiList;
    std::deque< T > firstDeque;
    for (size_t i = 0; i != size; ++i)
    {
      T value = detail::generateValue(T());
      fList.push_front(value);
      firstBiList.push_front(value);
      firstDeque.push_front(value);
    }
    List< T > secondBiList = firstBiList;
    std::deque< T > secondDeque = firstDeque;
    std::deque< T > thirdDeque = firstDeque;

    output << std::setprecision(1) << std::fixed;
    printRange(fList.cbegin(), fList.cend(), output);

    fList.sort(Compare());
    oddEvenSort(firstBiList.begin(), firstBiList.end(), Compare());
    secondBiList.sort(Compare());
    oddEvenSort(firstDeque.begin(), firstDeque.end(), Compare());
    QSort(secondDeque.begin(), secondDeque.end(), Compare());
    std::sort(thirdDeque.begin(), thirdDeque.end(), Compare());

    printRange(fList.cbegin(), fList.cend(), output);
    printRange(firstBiList.cbegin(), firstBiList.cend(), output);
    printRange(secondBiList.cbegin(), secondBiList.cend(), output);
    printRange(firstDeque.cbegin(), firstDeque.cend(), output);
    printRange(secondDeque.cbegin(), secondDeque.cend(), output);
    printRange(thirdDeque.cbegin(), thirdDeque.cend(), output);
  }
}
#endif
