#ifndef INPUT_NAMED_LIST
#define INPUT_NAMED_LIST

#include <iosfwd>
#include "list.hpp"

namespace erohin
{
  using int_t = int;
  using long_t = long long;
  using named_list = std::pair< std::string, List< int_t > >;
  void inputNamedList(std::istream & input, List< named_list > & result);
}
#endif
