#include "cmd.hpp"
#include <string>
#include <AVLTree.hpp>
#include "key_summ.hpp"

namespace sivkov
{
  void ascending(const AVLTree< int, std::string >& tree, KeySum& f)
  {
    tree.traverse_lnr(f);
  }

  void descending(const AVLTree< int, std::string >& tree, KeySum& f)
  {
    tree.traverse_rnl(f);
  }

  void breadth(const AVLTree< int, std::string >& tree, KeySum& f)
  {
    tree.traverse_breadth(f);
  }
}

