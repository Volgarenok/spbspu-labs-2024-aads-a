#ifndef INPUT_OUTPUT_HPP
#define INPUT_OUTPUT_HPP

#include <utility>

#include "list.hpp"

namespace vojuck
{
  using paired_list = std::pair< std::string, List< size_t > >;
  void inputLine(std::istream & in, paired_list & vertical);
  void inputLists(std::istream & in, List< paired_list> & result);
}
#endif
