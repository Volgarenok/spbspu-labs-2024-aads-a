#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <list.hpp>
#include <binarySearchTree.hpp>
#include <iosfwd>
#include <string>
#include <utility>

namespace zak = zakozhurnikova;
using dict = zak::BinarySearchTree< std::string, zak::BinarySearchTree< std::string, zak::List< std::string > > >;
using dictionaryOne = zak::BinarySearchTree< std::string, zak::List< std::string > >;

namespace zakozhurnikova
{
  void print(const List< std::string >& args, std::string& result, const dict& dictionary);
  void complement(List< std::string >& args, std::string& result, dict& dictionary);
  void intersect(List< std::string >& args, std::string& result, dict& dictionary);
  void doUnion(List< std::string >& args, std::string& result, dict& dictionary);
  void specificLetter(List< std::string >& args, std::string& result, dict& dictionary);
  void elimination(List< std::string >& args, std::string& result, dict& dictionary);
  void destruction(List< std::string >& args, std::string& result, dict& dictionary);
}

#endif
