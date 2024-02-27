#ifndef INPUTLIST_HPP
#define INPUTLIST_HPP
#include <istream>
#include "list.hpp"

namespace piyavkin
{
  std::pair< std::string, List< unsigned long long >* >* inputList(std::istream& in, size_t& size, size_t& max_size_list);
}
#endif
