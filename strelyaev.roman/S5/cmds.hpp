#ifndef CMDS_HPP
#define CMDS_HPP
#include <tree/binarySearchTree.hpp>

namespace strelyaev
{
  int traverseAscending(std::string& result, Tree< int, std::string >& tree);
  int traverseDescending(std::string& result, Tree< int, std::string >& tree);
  int TraverseBreadth(std::string& result, Tree< int, std::string >& tree);
}

#endif

