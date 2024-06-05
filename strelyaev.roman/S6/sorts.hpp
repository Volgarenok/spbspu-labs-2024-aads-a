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

}
#endif