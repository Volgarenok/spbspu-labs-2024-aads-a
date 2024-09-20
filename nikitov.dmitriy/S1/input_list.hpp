#ifndef INPUT_LIST_HPP
#define INPUT_LIST_HPP

#include <istream>
#include <string>
#include <list.hpp>

namespace nikitov
{
  void inputList(List< std::pair< std::string, List< size_t > > >& pairsList, std::istream& input);
}
#endif
