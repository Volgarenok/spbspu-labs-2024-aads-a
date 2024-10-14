#ifndef EMPTY_LIST_HPP
#define EMPTY_LIST_HPP

#include <string>
#include <vector>
#include "list.hpp"

namespace stepanov
{
  bool isEmptyList(std::vector<std::pair<std::string, List<size_t>>>& sequences);
}
#endif
