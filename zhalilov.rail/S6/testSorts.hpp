#ifndef TESTSORTS_HPP
#define TESTSORTS_HPP

#include <ostream>
#include <deque>
#include <forward_list>
#include <functional>
#include <random>

#include <list/list.hpp>

#include "sortAlgorithms.hpp"

namespace zhalilov
{
  template < class ForwardIt >
  void printNums(ForwardIt first, ForwardIt last, std::ostream &out)
  {
    ForwardIt next = first;
    ++next;
    while (next != last)
    {
      out << *first << ' ';
      ++first;
      ++next;
    }
    out << *first << '\n';
  }

  template < class T >
  T generateNumInRange(T first, T last)
  {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution< > dis(first, last);
    return static_cast< T >(dis(gen));
  }

  template < class T, class Compare >
  void testSorts(size_t size, std::ostream &out)
  {
    std::deque< T > nums(size);
    auto generator = std::bind(generateNumInRange< T >, -1000, 1000);
    std::generate(nums.begin(), nums.end(), generator);

    std::forward_list< T > implForwardOddEven(nums.cbegin(), nums.cend());
    std::forward_list< T > implForwardBucket(nums.cbegin(), nums.cend());
    List< T > myListBucket(nums.cbegin(), nums.cend());
    std::deque< T > deqOddEven(nums.cbegin(), nums.cend());
    std::deque< T > deqBucket(nums.cbegin(), nums.cend());
    std::deque< T > deqSort(nums.cbegin(), nums.cend());

    Compare comparer;
    oddEvenSort(implForwardOddEven.begin(), implForwardOddEven.end(), comparer);
    oddEvenSort(deqOddEven.begin(), deqOddEven.end(), comparer);

    bucketSort(implForwardBucket.begin(), implForwardBucket.end(), comparer, 10);
    bucketSort(myListBucket.begin(), myListBucket.end(), comparer, 10);
    bucketSort(deqBucket.begin(), deqBucket.end(), comparer, 10);

    std::sort(deqSort.begin(), deqSort.end(), comparer);

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
