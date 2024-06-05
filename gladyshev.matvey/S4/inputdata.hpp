#ifndef INPUTDATA_HPP
#define INPUTDATA_HPP

#include <fstream>
#include <string>

#include <avltree.hpp>

namespace gladyshev
{
  using mainDic = Tree< std::string, Tree< int, std::string > >;
  void read_dictionaries(std::ifstream& in, mainDic& dictionaries);
}

#endif
