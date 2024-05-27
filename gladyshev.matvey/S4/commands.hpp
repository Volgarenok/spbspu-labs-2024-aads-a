#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <string>

#include <avltree.hpp>

namespace gladyshev
{
  using dic = Tree< int, std::string >;
  using mainDic = Tree< std::string, Tree< int, std::string > >;
  void print_dictionary(const dic& dictionary);
  void print_dictionaries(const std::string& s, const mainDic& dictionaries);
  mainDic intersect(const std::string& s, const dic& dict1, const dic& dict2);
  mainDic complement(const std::string& s, const dic& dict1, const dic& dict2);
  mainDic union_dictionaries(const std::string& s, const dic& dict1, const dic& dict2);
  dic findName(const mainDic& dictionaries, const std::string& name);
}

#endif
