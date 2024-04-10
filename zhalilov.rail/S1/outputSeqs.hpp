#ifndef OUTPUTSEQ_HPP
#define OUTPUTSEQ_HPP

#include <iosfwd>
#include <utility>

#include <list/list.hpp>

namespace zhalilov
{
  using strListPair = std::pair< std::string, List< size_t > >;
  size_t countSum(const List< size_t > &list);
  std::ostream &outputSeqs(List< strListPair > sequences, std::ostream &output);
}

#endif
