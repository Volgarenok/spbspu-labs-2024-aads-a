#ifndef ITERATOR_FUNCTIONS_HPP
#define ITERATOR_FUNCTIONS_HPP

#include <cstddef>

namespace grechishnikov
{
  template< class Iterator >
  Iterator advance(Iterator iter, size_t n)
  {
    Iterator temp = iter;
    for (size_t i = 0; i < n; i++)
    {
      temp++;
    }
    return temp;
  }
}

#endif
