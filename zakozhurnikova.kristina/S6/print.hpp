#ifndef PRINT_HPP
#define PRINT_HPP
#include <ostream>
#include <iomanip>
#include <list.hpp>
#include <forward_list>

using namespace zakozhurnikova;

template < class list >
void print(std::ostream& out, const list& count)
{
  for (auto it = count.begin(); it != count.end(); ++it)
  {
    out << std::fixed << std::setprecision(1) << *it;
    auto temp = it;
    std::advance(temp, 1);
    if (temp != count.end())
    {
      out << ' ';
    }
  }
  out << '\n';
}

#endif
