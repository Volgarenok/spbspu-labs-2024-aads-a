#ifndef OUTPUT_LIST_HPP
#define OUTPUT_LIST_HPP

#include "inputList.hpp"
#include "forwardList.hpp"
#include <ostream>

namespace chernov
{
  void outNames(const List< namedNumberedList > & list, std::ostream& output);
  void outNumbers(std::ostream& output);
  void outSums(std::ostream& output);
}


#endif
