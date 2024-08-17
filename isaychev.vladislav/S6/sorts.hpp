#ifndef SORTS_HPP
#define SORTS_HPP

#include <utility>
#include <cstddef>

namespace isaychev
{

  template < class ForwardIt, class Cmp >
  ForwardIt do_partition(ForwardIt first, ForwardIt last, Cmp cmp)
  {
    if (first != last)
    {
      auto curr = first;
      for (++curr; curr != last;)
      {
        while (curr != last && cmp(*first, *curr))
        {
          ++curr;
        }
        if (curr != last)
        {
          std::swap(*curr, *first);
          ++first;
          std::swap(*curr, *first);
          ++curr;
        }
      }
    }
    return ++first;
  }


  template < class ForwardIt, class Cmp >
  void quick_sort(ForwardIt first, ForwardIt last, Cmp cmp)
  {
    auto temp = do_partition(first, last, cmp);
  }

/*  template < class BidIter, class Cmp >  // ne rabotaet poka
  void merge_sort(BidIter first, size_t size, Cmp cmp)
  {
    if (size != 1 || size != 0)
    {
      BidIter temp = first;
      size_t middle = size / 2;
      size_t remain = size - middle;
      for (size_t i = 0; i != middle; ++i)
      {
        ++temp;
      }
      merge_sort(first, middle, cmp);
      merge_sort(temp, remain, cmp);

      for (size_t i = 0; i < size - 1; ++i)
      {
        if (cmp(*temp, *first))
        {
          std::swap(*temp, *first);
        }
      }
    }
  }*/
}

#endif
