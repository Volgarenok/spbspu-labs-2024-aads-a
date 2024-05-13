#ifndef INPUT_HPP
#define INPUT_HPP

#include <AVLTree.hpp>

namespace sivkov
{
  void inputDictionary(AVLTree < std::string, AVLTree< size_t, std::string > >& treeOfdic, std::istream& in);
}
#endif

