#ifndef SORTING_ALGORITHMS_HPP
#define SORTING_ALGORITHMS_HPP
#include <iterator>
#include <algorithm>
#include <forward_list.hpp>

namespace zaitsev
{
  template< class ForwardIt, class Comapare >
  void shellSort(ForwardIt begin, ForwardIt end, Comapare cmp)
  {
    size_t size = std::distance(begin, end);
    size_t diff = size;
    while (diff > 1)
    {
      diff /= 2;
      ForwardIt front_start = begin;
      std::advance(front_start, diff);
      size_t swaps = 1;
      while (swaps != 0)
      {
        ForwardIt front = front_start;
        ForwardIt back = begin;
        swaps = 0;
        while (front != end)
        {
          if (cmp(*front, *back))
          {
            std::swap(*back, *front);
            ++swaps;
          }
          ++front;
          ++back;
        }
      }
    }
  }

  template< class RandomIt, class Comapare >
  void bucketSort(RandomIt begin, RandomIt end, Comapare cmp, size_t buckets_nmb = 2)
  {
    using T = typename std::iterator_traits< RandomIt >::value_type;
    using Flist_T = ForwardList< T >;
    using bucket_it_t = typename ForwardList< std::pair< T, Flist_T > >::iterator;
    using list_it_t = typename Flist_T::const_iterator;
    std::pair< RandomIt, RandomIt > bounds = std::minmax_element(begin, end);
    ForwardList< std::pair< T, Flist_T > > sups(1, { *bounds.second , Flist_T{} });
    T step = (*bounds.second - *bounds.first) / buckets_nmb;
    for (size_t i = buckets_nmb - 1; i > 0; --i)
    {
      sups.push_front({ *bounds.first + step * (buckets_nmb - i), Flist_T{} });
    }
    for (RandomIt i = begin; i != end; ++i)
    {
      bucket_it_t j = sups.begin();
      bool exit = false;
      while (!exit && j != sups.end())
      {
        exit = cmp((*j).first, *i) || !(cmp(*i, (*j).first) == cmp((*j).first, *i));
        if (exit)
        {
          (*j).second.push_front(*i);
        }
        ++j;
      }
    }
    for (bucket_it_t i = sups.begin(); i != sups.end(); ++i)
    {
      (*i).second.sort(cmp);
      for (list_it_t j = (*i).second.cbegin(); j != (*i).second.cend(); ++j, ++begin)
      {
        *begin = (*j);
      }
    }
  }
}
#endif
