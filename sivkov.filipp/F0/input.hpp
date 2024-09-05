#ifndef INPUT_HPP
#define INPUT_HPP

#include <AVLTree.hpp>

namespace sivkov
{
  AVLTree < std::string, AVLTree< std::string, std::string > > inputDictionary(std::istream& in);
}
#endif


