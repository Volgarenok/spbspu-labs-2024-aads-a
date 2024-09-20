#ifndef TREE_TRAVERSAL_CMDS_HPP
#define TREE_TRAVERSAL_CMDS_HPP

#include <UBST.hpp>
#include "funcObject.hpp"

namespace skuratov
{
  std::pair< int, std::string > isAscending(UBST< int, std::string >& map);
  std::pair< int, std::string > isDescending(UBST< int, std::string >& map);
  std::pair< int, std::string > isBreadth(UBST< int, std::string >& map);
}

#endif
