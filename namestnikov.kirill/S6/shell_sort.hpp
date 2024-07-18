#ifndef SHELL_SORT_HPP
#define SHELL_SORT_HPP

#include <cstddef>
#include <iterator>

namespace namestnikov
{
  template< class Iter, class Compare >
  void doShellSort(Iter begin, size_t size, Compare compare)
  {
    for (size_t gap = size / 2; gap > 0; gap /= 2)
    {
      for (size_t i = gap; i < size; ++i)
      {
        auto temp = *std::next(begin, i);
        size_t j = i;
        for (; ((j >= gap) && (compare(temp, *std::next(begin, j - gap)))); j -= gap)
        {
          *std::next(begin, j) = *std::next(begin, j - gap);
        }
        *std::next(begin, j) = temp;
      }
    }
  }
}

#endif
