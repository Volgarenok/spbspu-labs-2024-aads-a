#ifndef OUTPUT_RANGE_HPP
#define OUTPUT_RANGE_HPP

#include <ostream>

namespace isaychev
{
  template < class OutputIt >
  void output_range(std::ostream & out, OutputIt first, OutputIt last)
  {
    out << *first;
    for (++first; first != last; ++first)
    {
      out << " " << *first;
    }
  }
}

#endif
