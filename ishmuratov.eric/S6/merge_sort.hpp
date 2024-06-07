#ifndef SORT_HPP
#define SORT_HPP

namespace ishmuratov
{
  template < class BidirIt >
  BidirIt get_middle(BidirIt begin, BidirIt end)
  {
    BidirIt slow = begin;
    BidirIt fast = begin;
    while (fast != end)
    {
      ++fast;
      if (fast == end)
      {
        break;
      }
      ++fast;
      if (fast != end)
      {
        ++slow;
      }
    }
    return ++slow;
  }

  template < class BidirIt, class Compare >
  void merge_impl(BidirIt begin, BidirIt middle, BidirIt end, Compare comp)
  {
    BidirIt left = begin;
    BidirIt right = middle;

    while (left != middle && right != end)
    {
      if (comp(*left, *right))
      {
        ++left;
      }
      else
      {
        auto value = *right;
        BidirIt it = right;

        while (it != left)
        {
          BidirIt prev = it;
          --prev;
          *it = *prev;
          it = prev;
        }

        *left = value;

        ++left;
        ++middle;
        ++right;
      }
    }
  }

  template < class BidirIt, class Compare >
  void merge_sort(BidirIt begin, BidirIt end, Compare comp)
  {
    if (begin == end)
    {
      return;
    }

    BidirIt next = begin;
    if (++next == end)
    {
      return;
    }

    BidirIt middle = get_middle(begin, end);
    merge_sort(begin, middle, comp);
    merge_sort(middle, end, comp);
    merge_impl(begin, middle, end, comp);
  }
}

#endif
