#ifndef GRAPHS_BASE_HPP
#define GRAPHS_BASE_HPP
#include <ostream>
#include <string>
#include <map.hpp>

namespace zaitsev
{
  using args_flist = ForwardList< std::string >;
  using unit_t = Map< std::string, int >;
  using graph_t = Map< std::string, unit_t >;
  using base_t = Map < std::string, graph_t >;

  void createGraph(base_t& graphs, const args_flist& args, std::ostream&);
  void deleteGraph(base_t& graphs, const args_flist& args, std::ostream&);
  void addVertex(base_t& graphs, const args_flist& args, std::ostream&);
  void addEdge(base_t& graphs, const args_flist& args, std::ostream&);
  void mergeGraphs(base_t& graphs, const args_flist& args, std::ostream&);
}
#endif
