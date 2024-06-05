#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <iosfwd>
#include <string>
#include <tree/binarySearchTree.hpp>

namespace strelyaev
{
  void print(std::istream&, const Tree< std::string, Tree< int, std::string > >&, std::ostream&);
  void getComplement(std::istream&, Tree< std::string, Tree< int, std::string > >&);
  void getIntersect(std::istream&, Tree< std::string, Tree< int, std::string > >&);
  void getUnion(std::istream&, Tree< std::string, Tree< int, std::string > >&);
}

#endif
