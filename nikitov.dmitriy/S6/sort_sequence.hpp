#ifndef SORT_SEQUENCE_HPP
#define SORT_SEQUENCE_HPP

#include <string>
#include "iterators_functions.hpp"

namespace nikitov
{
  template< class T >
  void sortSequence(std::string sorting, std::string, size_t size)
  {
    std::cout << std::setprecision(1) << std::fixed;

    std::forward_list< T > fList;
    List< T > firstBiList;
    std::deque< T > firstDeque;
    for (size_t i = 0; i != size; ++i)
    {
      T value = std::rand();
      fList.push_front(value);
      firstBiList.push_back(value);
      firstDeque.push_back(value);
    }
    List< T > secondBiList = firstBiList;
    std::deque< T > secondDeque = firstDeque;
    std::deque< T > thirdDeque = firstDeque;
    printRange(fList.cbegin(), fList.cend(), std::cout);

    if (sorting == "ascending")
    {
      fList.sort(std::less< T >());
      oddEvenSort(firstBiList.begin(), firstBiList.end(), std::less< T >());
      secondBiList.sort(std::greater< T >());
      oddEvenSort(firstDeque.begin(), firstDeque.end(), std::less< T >());
      QSort(secondDeque.begin(), secondDeque.end(), std::less< T >());
      std::sort(thirdDeque.begin(), thirdDeque.end(), std::less< T >());
    }
    else if (sorting == "descending")
    {
      fList.sort(std::greater< T >());
      oddEvenSort(firstBiList.begin(), firstBiList.end(), std::greater< T >());
      secondBiList.sort(std::less< T >());
      oddEvenSort(firstDeque.begin(), firstDeque.end(), std::greater< T >());
      QSort(secondDeque.begin(), secondDeque.end(), std::greater< T >());
      std::sort(thirdDeque.begin(), thirdDeque.end(), std::greater< T >());
    }
    else
    {
      throw std::invalid_argument("Error: Wrong sorting parameter");
    }
    printRange(fList.cbegin(), fList.cend(), std::cout);
    printRange(firstBiList.cbegin(), firstBiList.cend(), std::cout);
    printRange(secondBiList.cbegin(), secondBiList.cend(), std::cout);
    printRange(firstDeque.cbegin(), firstDeque.cend(), std::cout);
    printRange(secondDeque.cbegin(), secondDeque.cend(), std::cout);
    printRange(thirdDeque.cbegin(), thirdDeque.cend(), std::cout);
  }
}
#endif