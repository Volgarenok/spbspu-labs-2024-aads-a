#ifndef SORTING_ALGORITHMS_HPP
#define SORTING_ALGORITHMS_HPP
#include <iterator>
#include <algorithm>
#include <queue>
#include <set>
#include <map.hpp>
#include <forward_list.hpp>

template< class ForwardIt, class Comapare >
void shellSort(ForwardIt begin, ForwardIt end, Comapare cmp, size_t size = 0)
{
  if (size == 0)
  {
    ForwardIt copy = begin;
    while (copy != end)
    {
      ++size;
      ++copy;
    }
  }
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
  using T = decltype (*begin);
  if (begin == end)
  {
    return;
  }
  T min_val = *begin;
  T max_val = *begin;
  size_t size = 1;
  bool not_sorted = false;
  RandomIt cur = begin;
  RandomIt pre_cur = begin;
  ++cur;
  while (cur != end)
  {
    min_val = cmp(*cur, min_val) ? *cur : min_val;
    max_val = cmp(max_val, *cur) ? *cur : max_val;
    not_sorted |= !cmp(*cur, *pre_cur);
    ++size;
    ++cur;
    ++pre_cur;
  }
  if (!not_sorted)
  {
    return;
  }
  using namespace zaitsev;
  ForwardList< std::pair< T, std::multiset< T, Comapare > > > sups(1, { max_val, std::multiset< T, Comapare > });
  using bucket_it_t = typename ForwardList< std::pair< T, std::multiset< T, Comapare > > >::iterator;
  T step = (max_val - min_val) / buckets_nmb;
  for (size_t i = 1; i < buckets_nmb; ++i)
  {
    sups.push_front({ min_val + step * i, std::multiset< T, Comapare > });
  }
  for (RandomIt i = begin; i != end; ++i)
  {
    bucket_it_t it = sups.begin();
    bool exit = false;
    while (!exit && it != sups.end())
    {
      exit = !cmp(*i, (*it).first) || !(cmp(*i, (*it).first) == cmp((*it).first, *i));
      if (exit)
      {
        (*it).second.insert(*i);
      }
      ++it;
    }
  }
}
#endif

