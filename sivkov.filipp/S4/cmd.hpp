#ifndef CMD_HPP
#define CMD_HPP

#include <AVLTree.hpp>

namespace sivkov
{
  void print(const AVLTree<std::string, AVLTree< size_t, std::string > >& treeOfdic, std::istream& in, std::ostream& out);
  void complement(AVLTree<std::string, AVLTree< size_t, std::string > >& treeOfdic, std::istream& in);
  void intersect(AVLTree<std::string, AVLTree< size_t, std::string > >& treeOfdic, std::istream& in);
  void unionCMD(AVLTree<std::string, AVLTree< size_t, std::string > >& treeOfdic, std::istream& in);
}

#endif
