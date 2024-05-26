#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <ostream>
#include <istream>
#include <tree.hpp>

namespace piyavkin
{
  using dic_t = Tree< std::string, Tree< std::string, size_t > >;
  void print(std::istream& in, std::ostream& out, const dic_t& dicts);
  void addDict(std::istream& in, dic_t& dicts);
  void changeDict(std::istream& in, dic_t& dicts);
}
#endif