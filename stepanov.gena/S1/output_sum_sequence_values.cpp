#include "output_sum_sequence_values.hpp"

namespace stepanov
{
  void output_sum_sequence_values(const List<size_t>& sums)
  {
    for (size_t i = 0; i < sums.size(); ++i)
    {
      std::cout << sums[i];
      if (i < sums.size() - 1)
      {
        std::cout << " ";
      }
    }
    std::cout << std::endl;
  }
}
