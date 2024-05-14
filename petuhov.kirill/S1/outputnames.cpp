#include "list.hpp"
#include <iostream>
#include <string>

namespace petuhov
{
  void outputNames(std::ostream& out, const List< std::pair< std::string, List< unsigned long long > > >& sequences)
  {
    bool first = true;
    for (ConstIterator< std::pair< std::string, List< unsigned long long > > > it = sequences.cbegin(); it != sequences.cend(); ++it)
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
