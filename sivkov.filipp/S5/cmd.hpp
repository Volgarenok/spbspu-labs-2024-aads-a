#ifndef CMD_HPP
#define CMD_HPP

#include <string>
#include <AVLTree.hpp>
#include "key_summ.hpp"

namespace sivkov
{
  void ascending(AVLTree< int, std::string >& tree, KeySum& f);
  void descending(AVLTree< int, std::string >& tree, KeySum& f);
  void breadth(AVLTree< int, std::string >& tree, KeySum& f);
}

#endif
