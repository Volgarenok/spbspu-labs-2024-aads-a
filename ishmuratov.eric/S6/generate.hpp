#ifndef GENERATE_HPP
#define GENERATE_HPP

#include <iostream>
#include <random>
#include <deque>
#include <list>
#include <forward_list>
#include <bdlist.hpp>
#include "merge_sort.hpp"
#include "quick_sort.hpp"

namespace ishmuratov
{
  int generate(int first, int second, std::mt19937 & range)
  {
    std::uniform_int_distribution< int > dist(first, second);
    return dist(range);
  }

  float generate(float first, float second, std::mt19937 & range)
  {
    std::uniform_real_distribution< float > dist(first, second);
    return dist(range);
  }

  template< class Iterator >
  void print(Iterator begin, Iterator end, std::ostream & output)
  {
    if (begin == end)
    {
      return;
    }
    output << *begin;
    ++begin;
    while (begin != end)
    {
      output << " " << *begin;
      ++begin;
    }
    output << "\n";
  }

  template< class T, class Compare >
  void test_sort(size_t size, std::ostream & output, std::mt19937 & range)
  {
    std::deque< T > nums;
    List< T > bilist_merge;
    T first = -1000;
    T second = 1000;
    for (size_t i = 0; i != size; ++i)
    {
      T num = generate(first, second, range);
      bilist_merge.pushBack(num);
      nums.push_back(num);
    }

    std::deque< T > deque_merge(nums.cbegin(), nums.cend());
    std::deque< T > deque_qsort(nums.cbegin(), nums.cend());
    std::list< T > bilist_standard(nums.cbegin(), nums.cend());
    std::forward_list< T > forward_standard(nums.cbegin(), nums.cend());
    std::deque< T > deque_standard(nums.cbegin(), nums.cend());

    merge_sort(bilist_merge.begin(), bilist_merge.end(), Compare());
    merge_sort(deque_merge.begin(), deque_merge.end(), Compare());
    quick_sort(deque_qsort.begin(), deque_qsort.end(), Compare());
    bilist_standard.sort(Compare());
    forward_standard.sort(Compare());
    std::sort(deque_standard.begin(), deque_standard.end(), Compare());

    print(nums.cbegin(), nums.cend(), output);
    print(bilist_merge.cbegin(), bilist_merge.cend(), output);
    print(deque_merge.cbegin(), deque_merge.cend(), output);
    print(deque_qsort.cbegin(), deque_qsort.cend(), output);
    print(bilist_standard.cbegin(), bilist_standard.cend(), output);
    print(forward_standard.cbegin(), forward_standard.cend(), output);
    print(deque_standard.cbegin(), deque_standard.cend(), output);
  }
}

#endif
