#include "commands.hpp"
#include <iostream>

void piyavkin::print(std::ostream& out, const std::string& str, const map_t& map)
{
  const tree_t res = map.at(str);
  if (res.empty())
  {
    out << "<EMPTY>";
  }
  else
  {
    out << str;
    for (auto it = res.cbegin(); it != res.cend(); ++it)
    {
      out << ' ' << it->first << ' ' << it->second;
    }
  }
  out << '\n';
}

void piyavkin::complement(map_t& res, const std::string& newDataSet, const std::string& lhs, const std::string& rhs)
{
  const tree_t rhsTree = res.at(rhs);
  const tree_t lhsTree = res.at(lhs);
  auto rhsIt = rhsTree.cbegin();
  tree_t newTree;
  for (auto it = lhsTree.cbegin(); it != lhsTree.cend(); ++it)
  {
    if (rhsIt->first < it->first)
    {
      newTree.insert(std::pair< int, std::string >(it->first, it->second));
      while (rhsIt != rhsTree.cend() && rhsIt->first < it->first)
      {
        ++rhsIt;
      }
    }
    else if (rhsIt->first > it->first)
    {
      newTree.insert(std::pair< int, std::string >(it->first, it->second));
    }
    else
    {
      if (rhsIt != rhsTree.cend())
      {
        ++rhsIt;
      }
    }
  }
  if (res.find(newDataSet) != res.end())
  {
    res.erase(newDataSet);
  }
  res[newDataSet] = newTree;
}

void piyavkin::unionF(map_t& res, const std::string& newDataSet, const std::string& lhs, const std::string& rhs)
{
  const tree_t rhsTree = res.at(rhs);
  const tree_t lhsTree = res.at(lhs);
  tree_t newTree;
  for (auto lhsIt = lhsTree.cbegin(); lhsIt != lhsTree.cend(); ++lhsIt)
  {
    newTree.insert(std::pair< int, std::string >(lhsIt->first, lhsIt->second));
  }
  for (auto it = rhsTree.cbegin(); it != rhsTree.cend(); ++it)
  {
    newTree.insert(std::pair< int, std::string >(it->first, it->second));
  }
  if (res.find(newDataSet) != res.end())
  {
    res.erase(newDataSet);
  }
  res[newDataSet] = newTree;
}

void piyavkin::intersect(map_t& res, const std::string& newDataSet, const std::string& lhs, const std::string& rhs)
{
  const tree_t rhsTree = res.at(rhs);
  const tree_t lhsTree = res.at(lhs);
  auto rhsIt = rhsTree.cbegin();
  tree_t newTree;
  for (auto it = lhsTree.cbegin(); it != lhsTree.cend(); ++it)
  {
    if (rhsIt->first == it->first)
    {
      newTree.insert(std::pair< int, std::string >(it->first, it->second));
      if (rhsIt != rhsTree.cend())
      {
        ++rhsIt;
      }
    }
    else if (rhsIt->first < it->first)
    {
      while (rhsIt != rhsTree.cend() && rhsIt->first < it->first)
      {
        ++rhsIt;
      }
    }
  }
  if (res.find(newDataSet) != res.end())
  {
    res.erase(newDataSet);
  }
  res[newDataSet] = newTree;
}
