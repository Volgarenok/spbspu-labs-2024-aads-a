#include "cmd.hpp"
#include <string>
#include <ostream>
#include <AVLTree.hpp>
#include "key_summ.hpp"

namespace sivkov
{
  void ascending(const AVLTree< int, std::string >& tree, KeySum& f, std::ostream& out)
  {
    KeySum res = tree.traverse_lnr(f);
    out << res.key_ << res.string_ << "\n";
  }

  void descending(const AVLTree< int, std::string >& tree, KeySum& f, std::ostream& out)
  {
    KeySum res = tree.traverse_rnl(f);
    out << res.key_ << res.string_ << "\n";
  }

  void breadth(const AVLTree< int, std::string >& tree, KeySum& f, std::ostream& out)
  {
    KeySum res = tree.traverse_breadth(f);
    out << res.key_ << res.string_ << "\n";
  }
}

