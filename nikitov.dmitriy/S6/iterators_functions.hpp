#ifndef ITERATORS_FUNCTIONS_HPP
#define ITERATORS_FUNCTIONS_HPP

#include <ostream>

namespace nikitov
{
  template< class Iterator >
  void printRange(Iterator begin, Iterator end, std::ostream& output)
  {
    while (begin != end)
    {
      output << *begin << ' ';
      ++begin;
    }
    output << '\n';
  }
}
#endif
