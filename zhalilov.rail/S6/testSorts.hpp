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

  template < class ContainerType, class ForwardIt, class SortingAlgo >
  void testContainerAndSort(ForwardIt first, ForwardIt last, SortingAlgo sort, std::ostream &out)
  {
    ContainerType container(first, last);
    sort(container.begin(), container.end());
    printNums(container.begin(), container.end(), out);
  }

  template < class T, class Compare >
  void testSorts(size_t size, std::ostream &out)
  {
    std::deque< T > nums(size);
    auto generator = std::bind(generateNumInRange< T >, -1000, 1000);
    std::generate(nums.begin(), nums.end(), generator);

    Compare comparer;
    using fwdList = std::forward_list< T >;
    using myList = List< T >;
    using stdDeq = std::deque< T >;

    using fwdListItType = typename std::forward_list< T >::iterator;
    using myListItType = typename List< T >::iterator;
    using deqItType = typename std::deque< T >::iterator;

    using namespace std::placeholders;
    auto fwdListOddEveSortFunc = std::bind(oddEvenSort< fwdListItType, Compare >, _1, _2, comparer);
    auto fwdListBucketSortFunc = std::bind(bucketSort< fwdListItType, Compare >, _1, _2, comparer, 10);
    auto myListBucketSortFunc = std::bind(bucketSort< myListItType, Compare >, _1, _2, comparer, 10);
    auto deqOddEvenSortFunc = std::bind(oddEvenSort< deqItType, Compare >, _1, _2, comparer);
    auto deqBucketSortFunc = std::bind(bucketSort< deqItType, Compare >, _1, _2, comparer, 10);
    auto deqStdSortFunc = std::bind(std::sort< deqItType, Compare >, _1, _2, comparer);

    printNums(nums.cbegin(), nums.cend(), out);

    testContainerAndSort< fwdList >(nums.cbegin(), nums.cend(), fwdListOddEveSortFunc, out);
    testContainerAndSort< fwdList >(nums.cbegin(), nums.cend(), fwdListBucketSortFunc, out);
    testContainerAndSort< myList >(nums.cbegin(), nums.cend(), myListBucketSortFunc, out);
    testContainerAndSort< stdDeq >(nums.cbegin(), nums.cend(), deqOddEvenSortFunc, out);
    testContainerAndSort< stdDeq >(nums.cbegin(), nums.cend(), deqBucketSortFunc, out);
    testContainerAndSort< stdDeq >(nums.cbegin(), nums.cend(), deqStdSortFunc, out);
  }
}

#endif
