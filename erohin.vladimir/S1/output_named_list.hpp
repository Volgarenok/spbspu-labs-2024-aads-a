#ifndef OUTPUT_NAMED_LIST
#define OUTPUT_NAMED_LIST

#include <iosfwd>
#include "list.hpp"
#include "named_number_list.hpp"

namespace erohin
{
  std::ostream & printNames(std::ostream & output, const List< named_list > & list);
  std::ostream & printSums(std::ostream & output, const List< long long > & sum);
  std::ostream & printElementsAndSums(std::ostream & output, const List< named_list > & list);
}
#endif

