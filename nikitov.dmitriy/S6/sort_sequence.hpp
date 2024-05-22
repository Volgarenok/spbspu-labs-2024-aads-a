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
  template< class T, class Compare >
  void sortSequence(std::string type, size_t size, std::ostream& output)
  {
    std::forward_list< T > fList;
    List< T > firstBiList;
    std::deque< T > firstDeque;
    for (size_t i = 0; i != size; ++i)
    {
      T value = 0;
      if (type == "ints")
      {
        value = rand();
      }
      else
      {
        value = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/RAND_MAX));
      }
      fList.push_front(value);
      firstBiList.push_back(value);
      firstDeque.push_back(value);
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
