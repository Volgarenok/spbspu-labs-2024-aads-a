#include "outputsums.hpp"
#include <iostream>
#include <stdexcept>
#include <limits>

namespace petuhov
{
  void outputSums(std::ostream& out, const List< unsigned long long >& sums)
  {
    bool first = true;
    for (ConstIterator< unsigned long long > sum_it = sums.cbegin(); sum_it != sums.cend(); ++sum_it)
    {
      if (!first)
      {
        out << " ";
      }
      first = false;
      out << *sum_it;
    }
    if (!sums.empty())
    {
      out << "\n";
    }

    unsigned long long total_sum = 0;
    for (ConstIterator<unsigned long long> sum_it = sums.cbegin(); sum_it != sums.cend(); ++sum_it)
    {
      if (*sum_it > 0 && total_sum > std::numeric_limits<unsigned long long>::max() - *sum_it)
      {
        throw std::overflow_error("Overflow occurred during summing");
      }
      total_sum += *sum_it;
    }
  }
}
