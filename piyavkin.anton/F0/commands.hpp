#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <ostream>
#include <istream>
#include <tree.hpp>

namespace piyavkin
{
  using tree_t = Tree< std::string, size_t >;
  using dic_t = Tree< std::string, tree_t >;
  using iterator = TreeIterator< std::string, tree_t >;
  void print(std::istream& in, std::ostream& out, const dic_t& dicts);
  iterator addDict(std::istream& in, dic_t& dicts);
  iterator cmdChange(std::istream& in, dic_t& dicts);
  iterator makeDict(std::istream& in, dic_t& dicts);
  iterator intersect(std::istream& in, dic_t& dicts);
  iterator unionD(std::istream& in, dic_t& dicts);
}
#endif