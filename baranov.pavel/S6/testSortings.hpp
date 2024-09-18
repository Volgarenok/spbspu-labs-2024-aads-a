#ifndef TEST_SORTINGS_HPP
#define TEST_SORTINGS_HPP
#include <iostream>
#include <random>
#include "generate.hpp"

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
}

#endif

