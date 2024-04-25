#ifndef COMANDS_HPP
#define COMANDS_HPP

namespace piyavkin
{
  using tree_t = Tree< int, std::string >;
  using map_t = Tree< std::string, tree_t >;
  void print(map_t& res, const map_t& rhs, const map_t& lhs);
  void complement(map_t& res, const map_t& rhs, const map_t& lhs);
  void unionF(map_t& res, const map_t& rhs, const map_t& lhs);
  void intersect(map_t& res, const map_t& rhs, const map_t& lhs);
  using com_t = Tree< std::string, void (*)(const map_t& res, const map_t& rhs, const map_t& lhs) >;
}
#endif