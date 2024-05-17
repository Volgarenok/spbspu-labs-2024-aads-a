#ifndef CMD_HPP
#define CMD_HPP

#include <string>
#include "AVLTree.hpp"
#include "key_summ.hpp"

namespace sivkov
{
  void ascending(const AVLTree< int, std::string >& tree, KeySum& f);
  void descending(const AVLTree< int, std::string >& tree, KeySum& f);
  void breadth(const AVLTree< int, std::string >& tree, KeySum& f);
}

#endif
