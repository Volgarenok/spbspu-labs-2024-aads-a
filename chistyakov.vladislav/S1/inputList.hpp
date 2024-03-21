#ifndef INPUT_HPP
#define INPUT_HPP

#include <istream>
#include "list.hpp"

namespace chistyakov
{
  void inputList(std::istreamI & input, List < std::pair < std::string, List < int > > > & list);
}

#endif
