#ifndef TEST_SORTINGS_HPP
#define TEST_SORTINGS_HPP
#include <iostream>
#include <random>
#include <deque>
#include <algorithm>
#include "generate.hpp"
#include "sortings.hpp"

namespace baranov
{
  template< typename Iterator >
  void printSequence(Iterator begin, Iterator end, std::ostream & out)
  {
    if (begin != end)
    {
      out << *begin;
      ++begin;
    }
    for (; begin != end; ++begin)
    {
      out << ' ' << *begin;
    }
  }

  template < typename T, typename Iterator >
  void fillSequence(Iterator begin, Iterator end, std::default_random_engine & generator)
  {
    for (auto it = begin; it != end; ++it)
    {
      *it = getRandomNumber(generator, T());
    }
  }

  template< typename T, typename Cmp >
  void testSortings(std::ostream & out, size_t size, Cmp cmp)
  {
    std::deque< T > nums(size);
    std::default_random_engine generator;
    fillSequence< T >(nums.begin(), nums.end(), generator);
    printSequence(nums.cbegin(), nums.cend(), out);
    out << '\n';

    std::deque< T > dequeInsertion(nums);
    std::deque< T > dequeQsort(nums);
    std::deque< T > dequeStdSort(nums);

    insertionSort(dequeInsertion.begin(), dequeInsertion.end(), cmp);
    quickSort(dequeQsort.begin(), dequeQsort.end(), cmp);
    std::sort(dequeStdSort.begin(), dequeStdSort.end(), cmp);

    printSequence(dequeInsertion.cbegin(), dequeInsertion.cend(), out);
    out << '\n';
    printSequence(dequeQsort.cbegin(), dequeQsort.cend(), out);
    out << '\n';
    printSequence(dequeStdSort.begin(), dequeStdSort.end(), out);

  }
}

#endif

