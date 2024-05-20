#ifndef TESTSORTS_HPP
#define TESTSORTS_HPP

#include <ostream>
#include <deque>
#include <forward_list>
#include <functional>

#include <list/list.hpp>

#include "sortAlgorithms.hpp"

namespace zhalilov
{
  template < class InputIt >
  void printNums(InputIt first, InputIt last, std::ostream &out)
  {
    InputIt next = first;
    next++;
    while (next != last)
    {
      out << *first << ' ';
      first++;
      next++;
    }
    out << *first << '\n';
  }

  template < class T >
  void testSorts(std::deque< T > nums, std::string direction, std::ostream &out)
  {
    std::function< bool (const T &, const T &) > comparer;
    if (direction == "ascending")
    {
      comparer = std::less< T >();
    }
    else if (direction == "descending")
    {
      comparer = std::greater< T >();
    }
    else
    {
      throw std::invalid_argument("testSorts: invalid direction");
    }

    std::forward_list< T > implForwardOddEven(nums.cbegin(), nums.cend());
    std::forward_list< T > implForwardBucket(nums.cbegin(), nums.cend());
    List< T > myListBucket(nums.cbegin(), nums.cend());
    std::deque< T > deqOddEven(nums.cbegin(), nums.cend());
    std::deque< T > deqBucket(nums.cbegin(), nums.cend());
    std::deque< T > deqSort(nums.cbegin(), nums.cend());

    oddEvenSort(implForwardBucket.begin(), implForwardBucket.end(), comparer);
    oddEvenSort(deqOddEven.begin(), deqOddEven.end(), comparer);

    printNums(nums.cbegin(), nums.cend(), out);
    printNums(implForwardOddEven.cbegin(), implForwardOddEven.cend(), out);
    printNums(implForwardBucket.cbegin(), implForwardBucket.cend(), out);
    printNums(myListBucket.cbegin(), myListBucket.cend(), out);
    printNums(deqOddEven.cbegin(), deqOddEven.cend(), out);
    printNums(deqBucket.cbegin(), deqBucket.cend(), out);
    printNums(deqSort.cbegin(), deqSort.cend(), out);
  }
}

#endif
