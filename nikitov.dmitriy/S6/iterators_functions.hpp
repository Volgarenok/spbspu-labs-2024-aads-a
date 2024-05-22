#ifndef ITERATORS_FUNCTIONS_HPP
#define ITERATORS_FUNCTIONS_HPP

#include <ostream>

namespace nikitov
{
  template< class Iterator >
  void printRange(Iterator begin, Iterator end, std::ostream& output)
  {
    if (begin != end)
    {
      output << *begin;
      while (++begin != end)
      {
        output << ' ' << *begin;
      }
      output << '\n';
    }
  }
}
#endif
