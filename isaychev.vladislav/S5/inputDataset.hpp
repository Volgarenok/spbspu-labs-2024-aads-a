#ifndef INPUTDATASET_HPP
#define INPUTDATASET_HPP

#include <tree/tree.hpp>
#include <string>
#include <iosfwd>

namespace isaychev
{
  using dataset_t = BSTree< int, std::string >;
  void inputDataset(std::istream & in, dataset_t & dataset);
}

#endif
