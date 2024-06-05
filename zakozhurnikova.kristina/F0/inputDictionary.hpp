#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP
#include <iosfwd>
#include <scopeGuard.hpp>
#include <binarySearchTree.hpp>
#include <list.hpp>

namespace zakozhurnikova
{
  using subDict = BinarySearchTree< std::string, List< std::string > >;
  using dict = BinarySearchTree< std::string, subDict >;
  bool isDictionary(const std::string& nameDictionary, const dict& dictionary);
  void inputDictionary(std::istream& in, dict& maps);
  void inputArgs(std::istream& in, List< std::string >& args);
  std::istream& operator>>(std::istream& in, subDict& dict);
}

#endif
