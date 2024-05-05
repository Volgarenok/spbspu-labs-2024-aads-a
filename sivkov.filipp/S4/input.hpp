#ifndef INPUT_HPP
#define INPUT_HPP

#include <map>
#include <string>
#include <istream>

namespace sivkov
{
  void inputDictionary(std::map < std::string, std::map< size_t, std::string > >& treeOfdic, std::istream& in);
}

#endif

