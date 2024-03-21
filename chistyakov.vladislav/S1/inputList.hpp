#ifndef INPUT_HPP
#define INPUT_HPP

#include <istream>
#include "list.hpp"

namespace chistyakov
{
  void inputList(std::istream & input, List < std::pair < std::string, List < int > > > & list);
  void inputNums(std::istream & input, List< int > & nums);
}

#endif
