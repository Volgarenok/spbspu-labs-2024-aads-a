#ifndef INPUT_LIST_HPP
#define INPUT_LIST_HPP

#include <fstream>
#include <string>
#include "list.hpp"

namespace nikitov
{
  List< std::pair< std::string, List< int >* >* > inputList(std::istream& input);
}
#endif
