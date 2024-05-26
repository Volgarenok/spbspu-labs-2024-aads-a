#ifndef SORTINGS_HPP
#define SORTINGS_HPP
#include <iterator>

namespace baranov
{
  template< typename Iterator, typename Comparator >
  void insertionSort(Iterator first, Iterator last, Comparator cmp)
  {
    for (Iterator i = std::next(first); i != last; ++i)
    {
      auto val = *i;
      Iterator j = std::prev(i);
      for (; j != last && !cmp(*j, val); --j)
      {
        *(std::next(j)) = *j;
      }
      *(++j) = val;
    }
  }
}

#endif

