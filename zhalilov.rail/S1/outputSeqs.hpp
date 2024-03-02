#ifndef OUTPUTSEQ_HPP
#define OUTPUTSEQ_HPP

#include <iosfwd>
#include <utility>

#include "list.hpp"

namespace zhalilov
{
  using pair = std::pair< std::string, List< size_t > >;
  std::ostream &outputSeqs(List< pair > sequences, std::ostream &output);
}

#endif
