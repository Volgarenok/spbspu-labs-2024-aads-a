#ifndef READ_DICTIONARIES_HPP
#define READ_DICTIONARIES_HPP

#include <istream>
#include <map>

namespace nikitov
{
  void readDictionaries(std::map< std::string, std::map< size_t, std::string > >& treeOfDictionaries, std::istream& input);
}
#endif