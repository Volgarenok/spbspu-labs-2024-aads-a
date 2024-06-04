#ifndef CMDS_HPP
#define CMDS_HPP

#include <string>
#include "AVLTree.hpp"

namespace skuratov
{
  void isPrint(std::istream& in, AVLTree< std::string, AVLTree< int, std::string > >& dictionary, std::ostream& out);
  void isComplement(std::istream& in, AVLTree< std::string, AVLTree< int, std::string > >& dictionary);
  void isIntersect(std::istream& in, AVLTree< std::string, AVLTree< int, std::string > >& dictionary);
  void isUnion(std::istream& in, AVLTree< std::string, AVLTree< int, std::string > >& dictionary);
}

#endif
