#ifndef INPUT_NAMED_LIST
#define INPUT_NAMED_LIST

#include <iosfwd>
#include "list.hpp"

namespace erohin
{
  using int_type = unsigned int;
  using long_type = unsigned long long;
  using named_list = std::pair< std::string, List< int_type > >;
  void inputNamedList(std::istream & input, List< named_list > & result);
}
#endif
