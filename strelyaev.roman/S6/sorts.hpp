#ifndef SORTS_HPP
#define SORTS_HPP
#include <iterator>
#include <utility>
namespace strelyaev
{
  template < class Iterator, class Compare >
  void bubble_sort(Iterator begin, Iterator end, Compare cmp)
  {
    bool sorted_once = false;
    do
    {
      auto current_first = begin;
      auto current_second = begin + 1;
      sorted_once = false;
      for (; current_second != end; current_first++, current_second++)
      {
        if (!cmp(*current_first, *current_second))
        {
          auto tmp = *current_first;
          *current_first = *current_second;
          *current_second = tmp;
          sorted_once = true;
        }
      }
    } while (sorted_once);
  }

  template < class Iterator, class Compare >
  void shell_sort(Iterator begin, Iterator end, Compare cmp)
  {
    auto size_it = begin;
    size_t size = 0;
    while (size_it != end)
    {
      size_it++;
      size++;
    }

    auto spacing = begin + size / 2;
    for (size_t interval = size / 2; interval > 0; interval /= 2)
    {
      auto temp = begin + interval;
      for (size_t i = interval; i < size; ++i)
      {
        auto number = *temp;
        auto tmp = temp;
        size_t j = i;
        for (; j >= interval && cmp(number, *(tmp - interval)); j -= interval)
        {
          auto next = tmp - interval;
          *tmp = *next;
          tmp = next;
        }
        *tmp = number;
        ++temp;
      }
      spacing = begin + interval / 2;
    }
  }

}
#endif
