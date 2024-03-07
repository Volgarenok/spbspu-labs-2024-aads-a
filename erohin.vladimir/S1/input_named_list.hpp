#ifndef INPUT_NAMED_LIST
#define INPUT_NAMED_LIST

#include <iosfwd>
#include "list.hpp"
#include "named_number_list.hpp"

namespace erohin
{
  void inputNamedList(std::istream & input, List< named_list > & result);
}
#endif
