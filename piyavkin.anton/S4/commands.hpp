#ifndef COMANDS_HPP
#define COMANDS_HPP
#include <ostream>
#include <tree.hpp>

namespace piyavkin
{
  using tree_t = Tree< int, std::string >;
  using map_t = Tree< std::string, tree_t >;
  void print(std::ostream& out, const std::string& str, const map_t& map);
  void complement(map_t& res, const std::string& newDataSet, const std::string& lhs, const std::string& rhs);
  void unionF(map_t& res, const std::string& newDataSet, const std::string& lhs, const std::string& rhs);
  void intersect(map_t& res, const std::string& newDataSet, const std::string& lhs, const std::string& rhs);
}
#endif
