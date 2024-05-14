#include "list.hpp"
#include <iostream>
#include <string>

namespace petuhov
{
  void outputNames(std::ostream& out, const List< std::pair< std::string, List< int > > >& sequences)
  {
    List< std::string > names;
    for (auto it = sequences.cbegin(); it != sequences.cend(); ++it)
    {
      names.push_front(it->first);
    }

    bool first = true;
    for (auto it = names.cbegin(); it != names.cend(); ++it)
    {
      if (!first)
      {
        out << " ";
      }
      out << *it;
      first = false;
    }
    out << "\n";
  }
}
