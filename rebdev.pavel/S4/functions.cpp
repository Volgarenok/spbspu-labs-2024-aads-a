#include "functions.hpp"

#include <vector>
#include <functional>
#include <algorithm>

void rebdev::print(std::ostream & out, const tree & outTree)
{
  std::vector< std::pair< long long int, std::string > > vec(outTree.begin(), outTree.end());
  std::sort(vec.begin(), vec.end(), std::less< std::pair< long long int, std::string > >());
  if (outTree.empty())
  {
    return;
  }
  auto it = vec.begin();
  while (it != vec.end())
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
