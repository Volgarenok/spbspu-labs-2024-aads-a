#ifndef TEST_SORTINGS_HPP
#define TEST_SORTINGS_HPP
#include <iostream>

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
}

#endif

