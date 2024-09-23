#include "treeTraversalCmds.hpp"

std::pair< int, std::string > skuratov::isAscending(UBST< int, std::string >& map)
{
  if (map.empty())
  {
    throw std::logic_error("<EMPTY>");
  }
  KeySumm result = {};
  result = map.traverseLnr(result);
  return std::make_pair(result.getKeyValue(), result.getNameString());
}

std::pair< int, std::string > skuratov::isDescending(UBST< int, std::string >& map)
{
  if (map.empty())
  {
    throw std::logic_error("<EMPTY>");
  }
  KeySumm result = {};
  result = map.traverseRnl(result);
  return std::make_pair(result.getKeyValue(), result.getNameString());
}

std::pair< int, std::string > skuratov::isBreadth(UBST< int, std::string >& map)
{
  if (map.empty())
  {
    throw std::logic_error("<EMPTY>");
  }
  KeySumm result = {};
  result = map.traverseBreadth(result);
  return std::make_pair(result.getKeyValue(), result.getNameString());
}
