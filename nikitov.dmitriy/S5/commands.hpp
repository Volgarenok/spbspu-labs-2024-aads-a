#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <string>
#include <tree.hpp>
#include "sum_keys.hpp"

namespace nikitov
{
  void traverseAscending(const Tree< int, std::string >& tree, SumKeys& f);
  void traverseDescending(const Tree< int, std::string >& tree, SumKeys& f);
  void traverseBreadth(const Tree< int, std::string >& tree, SumKeys& f);
}
#endif
