#include "outputsums.hpp"

namespace petuhov
{
  void outputSums(std::ostream& out, const List< int >& sums)
  {
    bool first = true;
    for (auto sum_it = sums.cbegin(); sum_it != sums.cend(); ++sum_it)
    {
      if (!first)
      {
        out << " ";
      }
      first = false;
      out << *sum_it;
    }
    out << "\n";
  }
}
