#ifndef SORTS_HPP
#define SORTS_HPP
#include <iterator>
#include <utility>
namespace strelyaev
{

  template < class Iterator, class Compare >
  void bubble_sort(Iterator begin, Iterator end, Compare cmp)
  {
    auto n = std::distance(begin, end);
    for (auto i = 0; i < n - 1; ++i)
    {
      for (auto j = 0; j < n - i - 1; ++j)
      {
        auto current = begin;
        std::advance(current, j);
        auto next = current;
        std::advance(next, 1);
        if (cmp(*next, *current))
        {
          auto temp = *current;
          *current = *next;
          *next = temp;
        }
      }
    }
  }

  template < typename Iterator, typename Compare >
  void shell(Iterator begin, Iterator end, Compare cmp)
  {
    auto n = std::distance(begin, end);
    for (auto gap = n / 2; gap > 0; gap /= 2)
    {
      for (auto i = gap; i < n; ++i)
      {
        auto temp = *(begin + i);
        auto j = i;
        while (j >= gap && cmp(temp, *(begin + j - gap)))
        {
          *(begin + j) = *(begin + j - gap);
          j -= gap;
        }
        *(begin + j) = temp;
      }
    }
  }
}

#endif