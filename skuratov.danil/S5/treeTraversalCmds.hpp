#ifndef TREE_TRAVERSAL_CMDS_HPP
#define TREE_TRAVERSAL_CMDS_HPP

#include <string>
#include <cstddef>
#include "UBST.hpp"

namespace skuratov
{
  std::pair< size_t, std::string > isAscending(UBST< size_t, std::string >&);
  std::pair< size_t, std::string > isDescending(UBST< size_t, std::string >&);
  std::pair< size_t, std::string > isBreadth(UBST< size_t, std::string >&);
}

#endif
