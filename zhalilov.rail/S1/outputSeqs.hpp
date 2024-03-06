#ifndef OUTPUTSEQ_HPP
#define OUTPUTSEQ_HPP

#include <iosfwd>
#include <utility>

#include "list.hpp"

namespace zhalilov
{
  using pair = std::pair< std::string, List< size_t > >;
  size_t countSum(const List< size_t > &list);
  std::ostream &outputSeqs(List< pair > sequences, std::ostream &output);
}

#endif
