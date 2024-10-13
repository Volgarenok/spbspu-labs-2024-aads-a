#include "sum_sequence_values.hpp"

namespace stepanov
{
  void sum_sequence_values(const std::vector<std::pair<std::string, List<size_t>>>& sequences)
  {
    std::vector<List<size_t>::const_iterator> iters;
    for (const auto& seq : sequences)
    {
      iters.push_back(seq.second.begin());
    }

    bool done = false;
    while (!done)
    {
      size_t sum = 0;
      done = true;
      bool has_values = false;

      for (size_t idx = 0; idx < iters.size(); ++idx)
      {
        if (iters[idx] != sequences[idx].second.end())
        {
          if (sum > std::numeric_limits<size_t>::max() - *iters[idx])
          {
            throw std::overflow_error("Overflow occurred during summation");
          }
          sum += *iters[idx];
          ++iters[idx];
          done = false;
          has_values = true;
        }
      }

      if (has_values)
      {
        std::cout << sum;
        if (!done)
        {
          std::cout << " ";
        }
      }
    }
    std::cout << std::endl;
  }
}
