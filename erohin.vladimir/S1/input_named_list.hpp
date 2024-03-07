#ifndef INPUT_NAMED_LIST
#define INPUT_NAMED_LIST

#include <iosfwd>
#include "list.hpp"

namespace erohin
{
  using named_list = std::pair< std::string, List< size_t > >;
  void inputNamedList(std::istream & input, List< named_list > & result);
}
#endif
