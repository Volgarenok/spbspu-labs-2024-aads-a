#include "commands.hpp"
#include <string>
#include <iostream>

void baranov::print(const treeOfTrees & trees, std::istream & in, std::ostream & out)
{
  std::string dictName;
  in >> dictName;
  const basicTree & tree = trees.at(dictName);
  if (tree.empty())
  {
    out << "<EMPTY>\n";
    return;
  }
  out << dictName;
  for (auto it = tree.cbegin(); it != tree.cend(); ++it)
  {
    out << ' ' << it->first << ' ' << it->second;
  }
  out << '\n';
}

void baranov::complement(treeOfTrees & trees, std::istream & in, std::ostream &)
{
  std::string newDictName;
  std::string firstDictName;
  std::string secondDictName;
  in >> newDictName >> firstDictName >> secondDictName;
  const basicTree & firstDict = trees.at(firstDictName);
  const basicTree & secondDict = trees.at(secondDictName);
  basicTree newDict;
  for (auto it = firstDict.cbegin(); it != firstDict.cend(); ++it)
  {
    if (secondDict.find(it->first) == secondDict.cend())
    {
      newDict.insert(*it);
    }
  }
  trees[newDictName] = newDict;
}

void baranov::intersect(treeOfTrees & trees, std::istream & in, std::ostream &)
{
  std::string newDictName;
  std::string firstDictName;
  std::string secondDictName;
  in >> newDictName >> firstDictName >> secondDictName;
  const basicTree & firstDict = trees.at(firstDictName);
  const basicTree & secondDict = trees.at(secondDictName);
  basicTree newDict;
  for (auto it = firstDict.cbegin(); it != firstDict.cend(); ++it)
  {
    if (secondDict.find(it->first) != secondDict.cend())
    {
      newDict.insert(*it);
    }
  }
  trees[newDictName] = newDict;
}

void baranov::unite(treeOfTrees & trees, std::istream & in, std::ostream &)
{
  std::string newDictName;
  std::string firstDictName;
  std::string secondDictName;
  in >> newDictName >> firstDictName >> secondDictName;
  const basicTree & firstDict = trees.at(firstDictName);
  const basicTree & secondDict = trees.at(secondDictName);
  basicTree newDict = firstDict;
  for (auto it = secondDict.cbegin(); it != secondDict.cend(); ++it)
  {
    newDict.insert(*it);
  }
  trees[newDictName] = newDict;
}

