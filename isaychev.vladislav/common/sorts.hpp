#ifndef SORTS_HPP
#define SORTS_HPP

#include <utility>
#include <iterator>

namespace isaychev
{
  namespace detail
  {
    template < class ForwardIt, class Cmp >
    ForwardIt do_partition(ForwardIt first, ForwardIt last, Cmp cmp)
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
      return first;
    }

    template < class RandomAcIt, class Cmp >
    void merge(RandomAcIt first, size_t middle, size_t size, Cmp cmp)
    {
      auto mid = first + middle;
      auto end = first + size;
      for (; first != mid && mid != end; ++first)
      {
        if (!cmp(*first, *mid))
        {
          for (auto i = mid; i != first; --i)
          {
            std::swap(*(std::prev(i)), *i);
          }
          ++mid;
        }
      }
    }
  }

  template < class ForwardIt, class Cmp >
  void quick_sort(ForwardIt first, ForwardIt last, Cmp cmp)
  {
    if (first != last)
    {
      auto temp = detail::do_partition(first, last, cmp);
      quick_sort(first, temp, cmp);
      quick_sort(++temp, last, cmp);
    }
  }

  template < class RandomAcIt, class Cmp >
  void merge_sort(RandomAcIt first, size_t size, Cmp cmp)
  {
    if (size != 1 && size != 0)
    {
      size_t middle = size / 2;
      merge_sort(first, middle, cmp);
      merge_sort(first + middle, size - middle, cmp);
      detail::merge(first, middle, size, cmp);
    }
  }
}

#endif
