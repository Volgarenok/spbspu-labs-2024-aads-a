#ifndef OUTPUT_LIST_HPP
#define OUTPUT_LIST_HPP

#include <fstream>
#include "list.hpp"

namespace nikitov
{
  void outputSequenceNames(const List< std::pair< std::string, List< size_t > > >& pairsList, size_t& maxSize, std::ostream& output);

  bool outputSequences(const List< std::pair< std::string, List< size_t > > >& pairsList, List< size_t >& sumsList, size_t maxSize, std::ostream& output);

  void outputSums(const List< size_t >& sumsList, std::ostream& output);
}
#endif
