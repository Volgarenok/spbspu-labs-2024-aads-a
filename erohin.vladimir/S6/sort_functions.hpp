#ifndef SORT_FUNCTIONS_HPP
#define SORT_FUNCTIONS_HPP

#include <algorithm>

namespace erohin
{
  template< class ForwardIt, class Comparator >
  void sort1(ForwardIt begin, ForwardIt end, Comparator cmp)
  {
    std::sort(begin, end, cmp);
  }

  template< class BidirectionalIt, class Comparator >
  void sort2(BidirectionalIt begin, BidirectionalIt end, Comparator cmp)
  {
    std::sort(begin, end, cmp);
  }

  template< class RandomAccessIt, class Comparator >
  void sort3(RandomAccessIt begin, RandomAccessIt end, Comparator cmp)
  {
    std::sort(begin, end, cmp);
  }
}

#endif
