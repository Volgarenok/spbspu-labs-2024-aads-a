#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <string>
#include <tree/tree.hpp>
#include "datasetSummarizer.hpp"

namespace isaychev
{
  using map_t = BSTree< int, std::string >;
  using functor_t = DatasetSummarizer;

  void trav_asc(const map_t & data, functor_t & f);
  void trav_des(const map_t & data, functor_t & f);
  void trav_brd(const map_t & data, functor_t & f);
}

#endif
