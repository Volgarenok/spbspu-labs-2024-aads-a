#ifndef TEST_SORTINGS_HPP
#define TEST_SORTINGS_HPP
#include <iostream>
#include <random>
#include <deque>
#include <algorithm>
#include <forward_list>
#include <list/list.hpp>
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
  void testSortings(std::ostream & out, size_t size)
  {
    Cmp cmp;
    std::deque< T > nums(size);
    std::default_random_engine generator;
    fillSequence< T >(nums.begin(), nums.end(), generator);
    printSequence(nums.cbegin(), nums.cend(), out);
    out << '\n';

    std::deque< T > dequeStdSort(nums);
    std::deque< T > dequeInsertion(nums);
    std::deque< T > dequeQsort(nums);
    List< T > listInsertion(nums.cbegin(), nums.cend());
    List< T > listQsort(nums.cbegin(), nums.cend());
    std::forward_list< T > fwdListQsort(nums.cbegin(), nums.cend());

    std::sort(dequeStdSort.begin(), dequeStdSort.end(), cmp);
    insertionSort(dequeInsertion.begin(), dequeInsertion.end(), cmp);
    quickSort(dequeQsort.begin(), dequeQsort.end(), cmp);
    insertionSort(listInsertion.begin(), listInsertion.end(), cmp);
    quickSort(listQsort.begin(), listQsort.end(), cmp);
    quickSort(fwdListQsort.begin(), fwdListQsort.end(), cmp);

    printSequence(dequeStdSort.begin(), dequeStdSort.end(), out);
    out << '\n';
    printSequence(dequeInsertion.cbegin(), dequeInsertion.cend(), out);
    out << '\n';
    printSequence(dequeQsort.cbegin(), dequeQsort.cend(), out);
    out << '\n';
    printSequence(listInsertion.cbegin(), listInsertion.cend(), out);
    out << '\n';
    printSequence(listQsort.cbegin(), listQsort.cend(), out);
    out << '\n';
    printSequence(fwdListQsort.cbegin(), fwdListQsort.cend(), out);
  }
}

#endif

