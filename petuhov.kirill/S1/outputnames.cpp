#include "outputnames.hpp"

namespace petuhov
{
  void outputNames(std::ostream& out, const List< std::pair< std::string, List< int > > >& sequences)
  {
    List< std::string > names;
    for (auto it = sequences.cbegin(); it != sequences.cend(); ++it)
    {
      names.push_front(it->first);
    }
    names.reverse();

    bool first = true;
    for (auto it = names.cbegin(); it != names.cend(); ++it)
    {
      if (!first)
      {
        out << " ";
      }
      first = false;
      out << *it;
    }
    out << "\n";
  }
}
