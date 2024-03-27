#ifndef GETSEQFROMSTREAM_HPP
#define GETSEQFROMSTREAM_HPP

#include <iosfwd>
#include <utility>

#include <list/list.hpp>

namespace zhalilov
{
  using strListPair = std::pair< std::string, List< size_t > >;
  void getSeqFromStream(List< strListPair > &sequences, std::istream &);
}

#endif
