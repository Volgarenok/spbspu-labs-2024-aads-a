#ifndef PRINT_HPP
#define PRINT_HPP
#include <forward_list>
#include <iomanip>
#include <list.hpp>
#include <ostream>

namespace zakozhurnikova
{
  template < class list >
  void print(std::ostream& out, const list& count)
  {
    out << std::fixed << std::setprecision(1);
    out << *count.begin();
    for (auto it = ++count.begin(); it != count.end(); ++it)
    {
      out << ' ' << *it;
    }
  }
}

#endif
