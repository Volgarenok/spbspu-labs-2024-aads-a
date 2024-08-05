#ifndef OUTPUT_NAMED_LIST
#define OUTPUT_NAMED_LIST

#include <iosfwd>
#include "list.hpp"
#include "input_named_list.hpp"

namespace erohin
{
  std::ostream & printNames(std::ostream & output, const List< named_list > & list);
  std::ostream & printList(std::ostream & output, const List< uint64_t > & list);
  void formOrderedNumLists(List < List< uint64_t > > & result, const List< named_list > & list);
  void formSumList(List< uint64_t > & result, const List < List< uint64_t > > & list);
}
#endif

