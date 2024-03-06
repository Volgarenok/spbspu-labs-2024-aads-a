#ifndef OUTPUTLIST_HPP
#define OUTPUTLIST_HPP

#include "list.hpp"

namespace zhalilov
{
  template < typename T >
  std::ostream &operator<<(std::ostream &os, const List< T > &list)
  {
    auto it = list.cbegin();
    auto end = list.cend();
    end--;
    while (it != end)
    {
      os << *it << " ";
      it++;
    }
    return os << *it;
  }
}

#endif
