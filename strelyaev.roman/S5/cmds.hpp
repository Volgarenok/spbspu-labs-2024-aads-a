#ifndef CMDS_HPP
#define CMDS_HPP
#include <tree/binarySearchTree.hpp>

namespace strelyaev
{
  int ascending(std::string& result, Tree< int, std::string >& tree);
  int descending(std::string& result, Tree< int, std::string >& tree);
  int breadth(std::string& result, Tree< int, std::string >& tree);
}

#endif

