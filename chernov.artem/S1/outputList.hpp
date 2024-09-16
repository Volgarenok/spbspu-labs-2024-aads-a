#ifndef OUTPUT_LIST_HPP
#define OUTPUT_LIST_HPP

#include <ostream>
#include <cstddef>
#include "inputList.hpp"
#include "forwardList.hpp"

namespace chernov
{
  void outNames(List< namedNumberedList > & list, std::ostream& output);
  void outNumbers(List< namedNumberedList >& list, List< size_t >& listSums, std::ostream& output);
  void outSums(List< size_t >& listSums, std::ostream& output);
  size_t maxDepth(const List< namedNumberedList >& list);
}


#endif
