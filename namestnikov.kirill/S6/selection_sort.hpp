#ifndef SELECTION_SORT_HPP
#define SELECTION_SORT_HPP

#include <cstddef>
#include <iterator>

namespace namestnikov
{
  template< class Iter, class Compare >
  void doSelectionSort(Iter begin, size_t size, Compare compare)
  {
    for (size_t i = 0; i < size - 1; ++i)
    {
      size_t minIndex = i;
      for (size_t j = i + 1; j < size; ++j)
      {
        if (compare(*std::next(begin, j), *std::next(begin, minIndex)))
        {
          minIndex = j;
        }
      }
      if (minIndex != i)
      {
        std::swap(*std::next(begin, minIndex), *std::next(begin, i));
      }
    }
  }
}

#endif
