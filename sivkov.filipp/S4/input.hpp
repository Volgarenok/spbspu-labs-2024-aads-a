#ifndef INPUT_HPP
#define INPUT_HPP

#include <AVLTree.hpp>

namespace sivkov
{
  AVLTree < std::string, AVLTree< size_t, std::string > > inputDictionary(std::istream& in);
}
#endif

