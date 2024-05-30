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
  void print(std::istream& in, const dic_t& dicts);
  void topFreq(std::istream& in, std::ostream& out, const dic_t& dicts);
  iterator input(std::istream&in, iterator it);
  iterator addDict(std::istream& in, dic_t& dicts);
  iterator cmdChange(std::istream& in, dic_t& dicts);
  iterator makeDict(std::istream& in, dic_t& dicts);
  iterator intersect(std::istream& in, dic_t& dicts);
  iterator unionD(std::istream& in, dic_t& dicts);
  iterator uniqueD(std::istream& in, dic_t& dicts);
  iterator addDtoD(std::istream& in, dic_t& dicts);
  iterator subD(std::istream& in, dic_t& dicts);
}
#endif
