#ifndef READ_DICTIONARIES_HPP
#define READ_DICTIONARIES_HPP

#include <istream>
#include <tree.hpp>

namespace nikitov
{
  void readDictionaries(Tree< std::string, Tree< size_t, std::string > >& treeOfDictionaries, std::istream& input);
}
#endif
