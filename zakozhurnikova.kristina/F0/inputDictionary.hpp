#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP
#include <iosfwd>
#include <scopeGuard.hpp>
#include <binarySearchTree.hpp>
#include <list.hpp>

namespace zakozhurnikova
{
  void inputDictionary(std::istream& in, BinarySearchTree< std::string, BinarySearchTree< std::string, List< std::string > > >& maps);
  void inputArgs(std::istream& in, List< std::string >& args);
}

#endif
