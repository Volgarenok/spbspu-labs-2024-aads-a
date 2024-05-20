#ifndef SORTALGORITHMS_HPP
#define SORTALGORITHMS_HPP

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
          std::swap(*next, *curr);
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
}

#endif
