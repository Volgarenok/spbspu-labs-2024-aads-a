#ifndef INPUT_NAMED_LIST
#define INPUT_NAMED_LIST

#include <iosfwd>
#include "list.hpp"

namespace erohin
{
  using named_list = std::pair< std::string, List< uint64_t > >;
  void inputNamedList(std::istream & input, named_list & result);
  void inputNamedListList(std::istream & input, List< named_list > & result);
}
#endif
