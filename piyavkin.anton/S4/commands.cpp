#include "commands.hpp"
#include <iostream>

void piyavkin::print(std::ostream& out, const std::string& str, const map_t& map)
{
  const tree_t res = map.at(str);
  out << str;
  if (res.empty())
  {
    out << " <EMPTY>";
  }
  else
  {
    for (auto it = res.cbegin(); it != res.cend(); ++it)
    {
      out << ' ' << it->first << ' ' << it->second;
    }
  }
  out << '\n';
}

void piyavkin::complement(map_t& res, const std::string& newDataSet, const std::string& rhs, const std::string& lhs)
{
  const tree_t rhsTree = res.at(rhs);
  const tree_t lhsTree = res.at(lhs);
  auto lhsIt = lhsTree.cbegin();
  tree_t newTree;
  for (auto it = rhsTree.cbegin(); it != rhsTree.cend(); ++it)
  {
    if (lhsIt->first > it->first)
    {
      newTree.insert(std::pair< int, std::string >(it->first, it->second));
    }
    else if (lhsIt->first < it->first)
    {
      newTree.insert(std::pair< int, std::string >(it->first, it->second));
      if (lhsIt != lhsTree.cend())
      {
        ++lhsIt;
      }
    }
    else
    {
      if (lhsIt != lhsTree.cend())
      {
        ++lhsIt;
      }
    }
  }
  res[newDataSet] = newTree;
}