#include "functions.hpp"

void rebdev::print(std::ostream & out, const tree & outTree)
{
  auto it = outTree.cbegin();
  while (it != outTree.cend())
  {
    std::cout << " " << (*it).first << " " << (*it).second;
    ++it
  }
  std::cout << '\n';
}
rebdev::tree rebdev::complement(const tree & firstTree, const tree & secondTree)
{
  tree newTree(firstTree);
  auto it = secondTree.cbegin();
  while (it != secondTree.cend())
  {
    newTree.erase((*it).first);
    ++it;
  }
  return newTree;
}
rebdev::tree rebdev::intersect(const tree & firstTree, const tree & secondTree)
{
  tree newTree(firstTree);
  auto it = secondTree.cbegin();
  while (it != secondTree.cend())
  {
    auto it2 = newTree.find((*it).first);
    if (it2 != newTree.end())
    {
      newTree.erase((*it).first);
    }
    ++it;
  }
  return newTree;
}
rebdev::tree rebdev::treeUnion(const tree & firstTree, const tree & secondTree)
{
  tree newTree;
  auto it = secondTree.cbegin();
  while (it != secondTree.cend())
  {
    auto it2 = newTree.find((*it).first);
    if (it2 != newTree.end())
    {
      newTree.insert(*it2);
    }
    ++it;
  }
  return newTree;
}
