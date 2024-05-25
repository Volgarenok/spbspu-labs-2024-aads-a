#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <ostream>
#include <tree.hpp>

namespace piyavkin
{
  using dic_t = Tree< std::string, Tree< std::string, size_t > >;
  void print(std::ostream& out, const std::string& name, const dic_t& dicts);
}
#endif