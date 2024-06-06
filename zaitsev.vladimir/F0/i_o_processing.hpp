#ifndef I_O_PROCESSING_HPP
#define I_O_PROCESSING_HPP
#include <iostream>
#include "graphs_base.hpp"

namespace zaitsev
{
  void readArgs(std::istream& in, args_flist& dest_args);
  void printHelp();
  void initBase(const char* file, base_t& base);
  std::ostream& listGraphs(const base_t& graphs, const args_flist&, std::ostream& out);
  std::ostream& printGraph(const base_t& graphs, const args_flist& args, std::ostream& out);
  void readGraph(base_t& graphs, const args_flist& args, std::ostream&);
  void writeGraph(const base_t& graphs, const args_flist& args, std::ostream&);
  void dump(const base_t& graphs, const args_flist& args, std::ostream&);
}
#endif
