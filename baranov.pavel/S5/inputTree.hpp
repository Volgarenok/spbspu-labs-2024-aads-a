#ifndef INPUT_TREE_HPP
#define INPUT_TREE_HPP
#include <istream>
#include <string>
#include <tree/tree.hpp>

namespace baranov
{
  void inputTree(std::istream & in, Tree< int, std::string > & tree);
}

#endif

