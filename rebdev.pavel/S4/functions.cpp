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
void rebdev::complement(tree & newTree, const tree & firstTree, const tree & secondTree)
{
  newTree = firstTree;
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
}
void rebdev::intersect(tree & newTree, const tree & firstTree, const tree & secondTree)
{
  auto it = firstTree.cbegin();
  while (it != firstTree.cend())
  {
    if (secondTree.find((*it).first) != secondTree.cend())
    {
      newTree.insert(*it);
    }
    ++it;
  }
}
void rebdev::treeUnion(tree & newTree, const tree & firstTree, const tree & secondTree)
{
  newTree = firstTree;
  auto it = secondTree.cbegin();
  while (it != secondTree.cend())
  {
    if (firstTree.find((*it).first) == firstTree.cend())
    {
      newTree.insert(*it);
    }
    ++it;
  }
}
