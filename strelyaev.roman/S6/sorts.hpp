#ifndef SORTS_HPP
#define SORTS_HPP
#include <iterator>
#include <utility>
namespace strelyaev
{

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