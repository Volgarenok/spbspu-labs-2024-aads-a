#ifndef SORTALGORITHMS_HPP
#define SORTALGORITHMS_HPP

#include <algorithm>

#include <list/list.hpp>

namespace zhalilov
{
  namespace detail
  {
    template < class Iterator, class Compare >
    bool oddEvenSortStep(Iterator first, Iterator last, Compare cmp, bool isOdd)
    {
      bool isSorted = true;
      Iterator curr = first;
      Iterator next = first;
      ++next;
      bool shouldCheck = isOdd;
      while (next != last)
      {
        if (shouldCheck && cmp(*next, *curr))
        {
          isSorted = false;
          std::iter_swap(next, curr);
        }
        ++curr;
        ++next;
        shouldCheck = !shouldCheck;
      }
      return isSorted;
    }
  }

  template < class Iterator, class Compare >
  void oddEvenSort(Iterator first, Iterator last, Compare cmp)
  {
    bool isSorted = false;
    while (!isSorted)
    {
      bool isSortedByOddStep = detail::oddEvenSortStep(first, last, cmp, true);
      bool isSortedByEvenStep = detail::oddEvenSortStep(first, last, cmp, false);
      isSorted = isSortedByOddStep && isSortedByEvenStep;
    }
  }

  template < class Iterator, class Compare >
  void bucketSort(Iterator first, Iterator last, Compare cmp, size_t numOfBuckets)
  {
    using numType = typename Iterator::value_type;
    auto minMax = std::minmax_element(first, last, cmp);
    auto minIt = minMax.first;
    auto maxIt = minMax.second;
    numType range = *maxIt - *minIt;
    numType step = range / numOfBuckets;
    List< List< numType > > buckets(numOfBuckets);
    Iterator currIt = first;
    while (currIt != last)
    {
      auto bucketsItCurr = buckets.begin();
      numType steppingValue = step;
      auto bucketsItAfterCurr = bucketsItCurr;
      ++bucketsItAfterCurr;
      while (cmp(steppingValue, *currIt) && bucketsItAfterCurr != buckets.end())
      {
        steppingValue += step;
        ++bucketsItCurr;
        ++bucketsItAfterCurr;
      }
      bucketsItCurr->push_back(*currIt);
      ++currIt;
    }

    for (auto it = buckets.begin(); it != buckets.end(); ++it)
    {
      oddEvenSort(it->begin(), it->end(), cmp);
    }

    auto containerToSortIt = first;
    for (auto it = buckets.begin(); it != buckets.end(); ++it)
    {
      for (auto currBucketIt = it->begin(); currBucketIt != it->end(); ++currBucketIt)
      {
        std::iter_swap(containerToSortIt, currBucketIt);
        ++containerToSortIt;
      }
    }
  }
}

#endif
