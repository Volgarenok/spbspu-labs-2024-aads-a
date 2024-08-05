#ifndef INPUTDICTIONARIES_HPP
#define INPUTDICTIONARIES_HPP

#include <iosfwd>
#include <string>
#include <tree/tree.hpp>

namespace isaychev
{
  using dataset_t = BSTree< int, std::string >;
  using map_t = BSTree< std::string, dataset_t >;
  void inputDictionaries(std::istream & in, map_t & dicts);
}

#endif
