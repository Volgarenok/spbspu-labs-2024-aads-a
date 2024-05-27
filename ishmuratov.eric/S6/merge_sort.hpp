#ifndef SORT_HPP
#define SORT_HPP

namespace ishmuratov
{
  template < typename BidirIt >
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

  template < typename BidirIt >
  void merge_impl(BidirIt begin, BidirIt middle, BidirIt end)
  {
    BidirIt left = begin;
    BidirIt right = middle;

    while (left != middle && right != end)
    {
      if (*left < *right)
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

  template <typename BidirIt>
  void merge_sort(BidirIt begin, BidirIt end)
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
    merge_sort(begin, middle);
    merge_sort(middle, end);
    merge_impl(begin, middle, end);
  }
}

#endif