#include "commands.hpp"

void nikitov::traverseAscending(const Tree< int, std::string >& tree, SumKeys& f)
{
  tree.traverseLNR(f);
}

void nikitov::traverseDescending(const Tree< int, std::string >& tree, SumKeys& f)
{
  tree.traverseRNL(f);
}

void nikitov::traverseBreadth(const Tree< int, std::string >& tree, SumKeys& f)
{
  tree.traverseBreadth(f);
}