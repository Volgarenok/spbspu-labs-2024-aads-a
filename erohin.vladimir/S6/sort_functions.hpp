#ifndef SORT_FUNCTIONS_HPP
#define SORT_FUNCTIONS_HPP

#include <algorithm>

namespace erohin
{
  template< class ForwardIt, class Compare >
  void sort1(ForwardIt begin, ForwardIt end, Compare cmp)
  {
    std::sort(begin, end, cmp);
  }

  template< class BidirectionalIt, class Compare >
  void sort2(BidirectionalIt begin, BidirectionalIt end, Compare cmp)
  {
    std::sort(begin, end, cmp);
  }

  template< class RandomAccessIt, class Compare >
  void sort3(RandomAccessIt begin, RandomAccessIt end, Compare cmp)
  {
    std::sort(begin, end, cmp);
  }
}

#endif
