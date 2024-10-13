#include "print_sequence_names.hpp"

namespace stepanov
{
  void print_sequence_names(const std::vector<std::pair<std::string, List<size_t>>>& sequences)
  {
    if (sequences.empty())
    {
      std::cout << "0" << std::endl;
      return;
    }
    for (auto it = sequences.begin(); it != sequences.end(); ++it)
    {
      std::cout << it->first;
      if (std::next(it) != sequences.end())
      {
        std::cout << " ";
      }
    }
    std::cout << std::endl;
  }
}

