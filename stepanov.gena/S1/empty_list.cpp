#include "empty_list.hpp"

namespace stepanov
{
  bool isEmptyList(const List<std::pair<std::string, List<size_t>>>& sequences)
  {
    for (const auto& seq : sequences)
    {
      if (!seq.second.empty())
      {
        return false;
      }
    }
    return true;
  }
}
