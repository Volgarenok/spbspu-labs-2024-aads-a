#include "list.hpp"
#include <iostream>
#include <string>

namespace petuhov
{
  void outputNames(std::ostream& out, const List< std::pair< std::string, List< size_t > > >& sequences)
  {
    std::string delimiter = "";
    for (ConstIterator< std::pair< std::string, List< size_t > > > it = sequences.cbegin(); it != sequences.cend(); ++it)
    {
      out << delimiter << it->first;
      delimiter = " ";
    }
    out << "\n";
  }
}

