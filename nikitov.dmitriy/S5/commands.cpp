#include "commands.hpp"

void nikitov::traverseAscending(const Tree< int, std::string >& tree, SumKeys& f)
{
  if (tree.empty())
  {
    throw std::logic_error("<EMPTY>");
  }
  f = tree.traverseLNR(f);
}

void nikitov::traverseDescending(const Tree< int, std::string >& tree, SumKeys& f)
{
  if (tree.empty())
  {
    throw std::logic_error("<EMPTY>");
  }
  f = tree.traverseRNL(f);
}

void nikitov::traverseBreadth(const Tree< int, std::string >& tree, SumKeys& f)
{
  if (tree.empty())
  {
    throw std::logic_error("<EMPTY>");
  }
  f = tree.traverseBreadth(f);
}
