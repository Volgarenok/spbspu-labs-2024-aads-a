#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <fstream>
#include <string>
#include "avltree.hpp"

namespace gladyshev
{
  using dic = Tree< std::string, size_t >;
  using mainDic = Tree< std::string, dic >;
  void print_dictionary(const dic& dictionary, std::ostream& out);
  void deleteDict(mainDic& dictionaries, std::istream& in);
  void deleteName(mainDic& dictionaries, std::istream& in);
  void save(const mainDic& dictionaries, std::istream& in, std::ofstream& outFile);
  void print_dictionaryL(const dic& dictionary, size_t n, std::ostream& out);
  void print_dictionariesL(const mainDic& dictionaries, std::istream& in, std::ostream& out);
  void print_dictionaries(const mainDic& dictionaries, std::istream& in, std::ostream& out);
  dic intersectImpl(const dic& dict1, const dic& dict2);
  void intersect(mainDic& dictionaries, std::istream& in);
  void addelem(mainDic& dictionaries, std::istream& in);
  void addition(mainDic& dictionaries, std::istream& in);
  dic additionImpl(const dic& dict1, const dic& dict2);
  void complement(mainDic& dictionaries, std::istream& in);
  dic complementImpl(const dic& dict1, const dic& dict2);
}

#endif
