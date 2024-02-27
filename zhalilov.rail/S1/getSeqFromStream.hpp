#ifndef GETSEQFROMSTREAM_HPP
#define GETSEQFROMSTREAM_HPP

#include <iosfwd>
#include <utility>

#include "list.hpp"

namespace zhalilov
{
  using pair = std::pair< std::string, List< size_t > >;
  void getSeqFromStream(List< pair > &sequences, std::istream &);
}

#endif
