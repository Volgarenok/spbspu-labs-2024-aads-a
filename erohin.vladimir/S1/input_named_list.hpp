#ifndef INPUT_NAMED_LIST
#define INPUT_NAMED_LIST

#include <iosfwd>
#include "list.hpp"

namespace erohin
{
  using int_t = unsigned long long;
  using named_list = std::pair< std::string, List< int_t > >;
  void inputNamedList(std::istream & input, named_list & result);
  void inputNamedListList(std::istream & input, List< named_list > & result);
}
#endif
