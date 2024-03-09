#ifndef OUTPUT_NAMED_LIST
#define OUTPUT_NAMED_LIST

#include <iosfwd>
#include "list.hpp"
#include "input_named_list.hpp"

namespace erohin
{
  std::ostream & printNames(std::ostream & output, const List< named_list > & list);
  std::ostream & printSums(std::ostream & output, const List< size_t > & sum);
  std::ostream & printElementsAndSums(std::ostream & output, const List< named_list > & list);
  std::ostream & printNumList(std::ostream & output, const List< size_t > & list);
  void formOrderedNumLists(List < List< size_t > > & result, const List< named_list > & list);
  void formSumList(List< size_t > & result, const List < List< size_t > > & list);
}
#endif

