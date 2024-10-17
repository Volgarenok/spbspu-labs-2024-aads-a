#ifndef INPUTDATA_HPP
#define INPUTDATA_HPP

#include <istream>
#include <fstream>
#include <string>

#include "hash_table.hpp"

namespace prisyach
{
  using dic = HashTable< std::string, int >;
  using mainDic = HashTable< std::string, dic >;
  void makeDict(mainDic& finres, std::ifstream& file, std::istream& in);
  void makeDictLen(mainDic& finres, std::ifstream& file, std::istream& in);
  void read_dictionaries(std::ifstream& in, mainDic& dictionaries);
}

#endif
