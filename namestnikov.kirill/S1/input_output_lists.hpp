#ifndef INPUT_OUTPUT_LISTS_HPP
#define INPUT_OUTPUT_LISTS_HPP

#include <iostream>
#include "forward_list.hpp"

namespace namestnikov
{
  using namedLists = std::pair< std::string, ForwardList< unsigned long long > >;
  void inputLists(std::istream & in, ForwardList< namedLists > & dataList);
  void outputNames(std::ostream & out, ForwardList< namedLists > & dataList, size_t & maxSize);
  void outputNumsAndSums(std::ostream & out, const ForwardList< namedLists > & dataList, size_t maxSize);
  bool haveNumbers(const ForwardList< namedLists > & dataList);
}

#endif
