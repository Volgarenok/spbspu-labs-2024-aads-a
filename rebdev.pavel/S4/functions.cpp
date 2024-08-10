#include "functions.hpp"

void rebdev::print(std::ostream & out, const tree & outTree)
{
  if (outTree.empty())
  {
    return;
  }
  auto it = outTree.cbegin();
  while (it != outTree.cend())
  {
    out << " " << (*it).first << " " << (*it).second;
    ++it;
  }
  std::cout << '\n';
}
rebdev::tree rebdev::complement(const tree & firstTree, const tree & secondTree)
{
  tree newTree(firstTree);
  auto it = secondTree.cbegin();
  while (it != secondTree.cend())
  {
    if (firstTree.find((*it).first) == firstTree.cend())
    {
      newTree.insert(*it);
    }
    else
    {
      newTree.erase((*it).first);
    }
    ++it;
  }
  return newTree;
}
rebdev::tree rebdev::intersect(const tree & firstTree, const tree & secondTree)
{
  tree newTree;
  auto it = firstTree.cbegin();
  while (it != firstTree.cend())
  {
    if (secondTree.find((*it).first) != secondTree.cend())
    {
      newTree.insert(*it);
    }
    ++it;
  }
  return newTree;
}
rebdev::tree rebdev::treeUnion(const tree & firstTree, const tree & secondTree)
{
  tree newTree(firstTree);
  auto it = secondTree.cbegin();
  while (it != secondTree.cend())
  {
    if (firstTree.find((*it).first) == firstTree.cend())
    {
      newTree.insert(*it);
    }
    ++it;
  }
  return newTree;
}
