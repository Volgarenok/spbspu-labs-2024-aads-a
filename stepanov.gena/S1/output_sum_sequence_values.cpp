#include "output_sum_sequence_values.hpp"

namespace stepanov
{
  void output_sum_sequence_values(const List<size_t>& sums)
  {
    for (size_t i = 0; i < sums.size(); ++i)
    {
      if (i > 0)
      {
        std::cout << " ";
      }
      std::cout << sums[i];
    }
    std::cout << "\n";
  }
}
