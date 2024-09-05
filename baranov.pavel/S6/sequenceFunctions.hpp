#ifndef SEQUENCE_OPERATIONS
#define SEQUENCE_OPERATIONS
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

