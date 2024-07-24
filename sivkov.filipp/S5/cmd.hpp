#ifndef CMD_HPP
#define CMD_HPP

#include <string>
#include <AVLTree.hpp>
#include "key_summ.hpp"

namespace sivkov
{
  void ascending(const AVLTree< int, std::string >& tree, KeySum& f, std::ostream& out);
  void descending(const AVLTree< int, std::string >& tree, KeySum& f, std::ostream& out);
  void breadth(const AVLTree< int, std::string >& tree, KeySum& f, std::ostream& out);
}

#endif

