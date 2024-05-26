#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <binarySearchTree.hpp>
#include <iosfwd>
#include <list.hpp>
#include <string>
#include <utility>

namespace zak = zakozhurnikova;
using dict = zak::BinarySearchTree< std::string, zak::BinarySearchTree< std::string, zak::List< std::string > > >;
using dictionaryOne = zak::BinarySearchTree< std::string, zak::List< std::string > >;

namespace zakozhurnikova
{
  void print(const List< std::string >& args, const dict& dictionary);
  void complement(List< std::string >& args, dict& dictionary);
  void intersect(List< std::string >& args, dict& dictionary);
  void doUnion(List< std::string >& args, dict& dictionary);
  void specificLetter(List< std::string >& args, dict& dictionary);
  void elimination(List< std::string >& args, dict& dictionary);
  void destruction(List< std::string >& args, dict& dictionary);
  void addition(List< std::string >& args, dict& dictionary);
  void palindrome(List< std::string >& args, dict& dictionary);
  void rider(List< std::string >& args, dict& dictionary);
  void interpreter(List< std::string >& args, dict& dictionary);
  void save(List< std::string >& args, dict& dictionary);
}

#endif
