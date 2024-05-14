#include "list.hpp"
#include <iostream>
#include <string>

namespace petuhov
{
  void outputNames(std::ostream& out, const List< std::pair< std::string, List< int > > >& sequences)
  {
    bool first = true;
    for (auto it = sequences.cbegin(); it != sequences.cend(); ++it)
    {
      if (!first)
      {
        out << " ";
      }
      out << it->first;
      first = false;
    }
    out << "\n";
  }
}
