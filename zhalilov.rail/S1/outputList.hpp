#ifndef OUTPUTLIST_HPP
#define OUTPUTLIST_HPP

#include <ostream>

#include <list/list.hpp>

namespace zhalilov
{
  template < typename T >
  std::ostream &outputList(std::ostream &os, const List< T > &list)
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
