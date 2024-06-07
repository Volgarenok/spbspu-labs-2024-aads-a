#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <iosfwd>
#include <string>
#include <utility>
#include <list.hpp>
#include <binarySearchTree.hpp>

namespace zak = zakozhurnikova;
using dict = zak::BinarySearchTree< std::string, zak::BinarySearchTree< std::string, zak::List< std::string > > >;
using dictionaryOne = zak::BinarySearchTree< std::string, zak::List< std::string > >;

namespace zakozhurnikova
{
  void print(const List< std::string >& args, std::ostream& out, const dict& dictionary);
  void complement(List< std::string >& args, dict& dictionary);
  void intersect(List< std::string >& args, dict& dictionary);
  void doUnion(List< std::string >& args, dict& dictionary);
  void specificLetter(List< std::string >& args, dict& dictionary);
  void elimination(List< std::string >& args, dict& dictionary);
  void destruction(const List< std::string >& args, dict& dictionary);
  void addition(const List< std::string >& args, dict& dictionary);
  void palindrome(const List< std::string >& args, dict& dictionary);
  void rider(List< std::string >& args, dict& dictionary);
  void interpreter(const List< std::string >& args, dict& dictionary);
  void save(const List< std::string >& args, const dict& dictionary);
  void doAddDictionary(const List< std::string >&, std::istream& in, dict& dictionary);
}

#endif
