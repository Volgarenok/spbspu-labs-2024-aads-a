#include "cmd.hpp"
#include <string>
#include <AVLTree.hpp>
#include "key_summ.hpp"
namespace sivkov
{
  void ascending(AVLTree< int, std::string >& tree, KeySum& f)
  {
    tree.iterLnr(f);
  }

  void descending(AVLTree< int, std::string >& tree, KeySum& f)
  {
    tree.iterRnl(f);
  }

  void breadth(AVLTree< int, std::string >& tree, KeySum& f)
  {
    tree.iterBfs(f);
  }
}
