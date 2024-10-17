#include "list.hpp"
#include <iostream>
#include <stdexcept>
#include <limits>

namespace petuhov
{
  void outputSums(std::ostream& out, const List< size_t >& sums)
  {
    if (sums.empty())
    {
      return;
    }

    ConstIterator< size_t > sum_it = sums.cbegin();
    out << *sum_it;
    ++sum_it;
    for (; sum_it != sums.cend(); ++sum_it)
    {
      out << " " << *sum_it;
    }
    out << "\n";

    size_t total_sum = 0;
    for (sum_it = sums.cbegin(); sum_it != sums.cend(); ++sum_it)
    {
      if (*sum_it > 0 && total_sum > std::numeric_limits< size_t >::max() - *sum_it)
      {
        throw std::overflow_error("Overflow occurred during summing");
      }
      total_sum += *sum_it;
    }
  }
}
