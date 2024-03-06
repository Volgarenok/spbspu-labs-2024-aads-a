#ifndef INPUT_NAMED_LIST
#define INPUT_NAMED_LIST

#include <iosfwd>
#include "list.hpp"

namespace erohin
{
  struct named_list
  {
    std::string name;
    List< int > number_list;
  };
  void input_named_list(std::istream & input, List< named_list > & result);
}
#endif
