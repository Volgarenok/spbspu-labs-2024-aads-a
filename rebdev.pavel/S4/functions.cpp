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
  tree treeToSwap(firstTree);
  auto it = secondTree.cbegin();
  while (it != secondTree.cend())
  {
    if (firstTree.find((*it).first) == firstTree.cend())
    {
      treeToSwap.insert(*it);
    }
    else
    {
      treeToSwap.erase((*it).first);
    }
    ++it;
  }
  newTree.swap(treeToSwap);
}
void rebdev::intersect(tree & newTree, const tree & firstTree, const tree & secondTree)
{
  tree treeToSwap;
  auto it = firstTree.cbegin();
  while (it != firstTree.cend())
  {
    if (secondTree.find((*it).first) != secondTree.cend())
    {
      treeToSwap.insert(*it);
    }
    ++it;
  }
  newTree.swap(treeToSwap);
}
void rebdev::treeUnion(tree & newTree, const tree & firstTree, const tree & secondTree)
{
  tree treeToSwap(firstTree);
  auto it = secondTree.cbegin();
  while (it != secondTree.cend())
  {
    if (firstTree.find((*it).first) == firstTree.cend())
    {
      treeToSwap.insert(*it);
    }
    ++it;
  }
  newTree.swap(treeToSwap);
}
