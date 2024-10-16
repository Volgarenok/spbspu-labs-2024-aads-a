#ifndef EMPTY_LIST_HPP
#define EMPTY_LIST_HPP

#include <string>
#include <vector>
#include "list.hpp"

namespace stepanov
{
  bool isEmptyList(const List<std::pair<std::string, List<size_t>>>& sequences);
}
#endif
