#ifndef INPUTOUTPUTLIST_HPP
#define INPUTOUTPUTLIST_HPP

#include <istream>
#include <utility>
#include <string>
#include <cstddef>
#include "list.hpp"

namespace chistyakov
{
  void inputList(std::istream & input, List < std::pair < std::string, List < size_t > > > & list);
  size_t maxDigit(List < std::pair < std::string, List < size_t > > > & list);
  void outPutNames(List < std::pair < std::string, List < size_t > > > & list);
  void outPutNums(List < std::pair < size_t, List < size_t > > > & list);
  void outPutSums(List < std::pair < size_t, List < size_t > > > & list);
}

#endif
