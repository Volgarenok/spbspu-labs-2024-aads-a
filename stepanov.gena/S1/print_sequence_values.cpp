#include "print_sequence_values.hpp"

namespace stepanov
{
  void print_sequence_values(const List<std::pair<std::string, List<size_t>>>& sequences)
  {
    List<List<size_t>::const_iterator> iters;
    for (const auto& seq : sequences)
    {
      iters.push_back(seq.second.begin());
    }

    bool done = false;
    while (!done)
    {
      done = true;
      bool has_output = false;
      for (size_t idx = 0; idx < iters.size(); ++idx)
      {
        if (iters[idx] != sequences[idx].second.end())
        {
          std::cout << *iters[idx];
          if (idx + 1 < iters.size())
          {
            std::cout << " ";
          }
          ++iters[idx];
          done = false;
          has_output = true;
        }
      }
      if (has_output)
      {
        std::cout << std::endl;
      }
    }
  }
}
