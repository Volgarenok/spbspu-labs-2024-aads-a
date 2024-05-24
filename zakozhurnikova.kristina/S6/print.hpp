#ifndef PRINT_HPP
#define PRINT_HPP
#include <forward_list>
#include <iomanip>
#include <ostream>
#include <list.hpp>

namespace zakozhurnikova
{
  template < class It >
  void print(std::ostream& out, It begin, It end)
  {
    out << std::fixed << std::setprecision(1);
    out << *begin;
    for (auto it = ++begin; it != end; ++it)
    {
      out << ' ' << *it;
    }
  }
}

#endif
